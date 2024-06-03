#include "testparser.h"

TestParser::TestParser() {}

bool TestParser::loadFromFile(QString filepath) {
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open the file:" << file.errorString();
        return false;
    }
    QByteArray jsonData = file.readAll();
    file.close();
    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &error);
    if (error.error != QJsonParseError::NoError) {
        qDebug() << "Failed to parse JSON:" << error.errorString();
        return false;
    }
    this->doc = jsonDoc;
    return true;
}

QList<Test> TestParser::tests() {
    QList<Test> tests;

    QJsonArray data = this->doc.array();
    for (const auto &jsonValue : data) {
        if (jsonValue.isObject()) {
            QJsonObject testJson = jsonValue.toObject();
            // name
            QString name = testJson["name"].toString();

            // desc
            QString desc = testJson["desc"].toString();

            // func
            size_t func_index = testJson["function_index"].toInt();

            QList<double> x_border;
            QJsonObject x_borderObj = testJson["x_border"].toObject();
            x_border.append(x_borderObj["start"].toDouble());
            x_border.append(x_borderObj["end"].toDouble());
            x_border.append(x_borderObj["step"].toDouble());

            QList<double> z_border;
            QJsonObject z_borderObj = testJson["z_border"].toObject();
            z_border.append(z_borderObj["start"].toDouble());
            z_border.append(z_borderObj["end"].toDouble());
            z_border.append(z_borderObj["step"].toDouble());

            QList<double> transformations;
            QJsonObject transformationsObj = testJson["transformations"].toObject();
            transformations.append(transformationsObj["x_turn"].toDouble());
            transformations.append(transformationsObj["y_turn"].toDouble());
            transformations.append(transformationsObj["z_turn"].toDouble());

            int scale = testJson["scale_coefficient"].toInt();

            tests << Test(name, desc, func_index, x_border, z_border, transformations, scale, true);
        }
    }
    return tests;
}

// [
//     {
//         "name": "Test 1",
//         "desc": "Функция cos(x) * sin(z)",
//         "function_index": 1,
//         "x_border": { "start" : -5, "end" : 5, "step" : 0.1 },
//         "z_border": { "start" : -5, "end" : 5, "step" : 0.1 },
//         "transformations": { "x_turn" : 20, "y_turn" : 10, "z_turn" : 0 },
//         "scale_coefficient": 40
//     }
// ]
