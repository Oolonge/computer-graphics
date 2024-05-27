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
    algorithm_t method;
    figure_type_t figure;

    QJsonArray data = this->doc.array();
    for (const auto &jsonValue : data) {
        if (jsonValue.isObject()) {
            QJsonObject testJson = jsonValue.toObject();
            // name
            QString name = testJson["name"].toString();

            // desc
            QString desc = testJson["desc"].toString();

            // method
            QString method_str = testJson["method"].toString();
            method = parseMethod(method_str);

            // figure
            QString figure_str = testJson["figure"].toString();
            figure = parseFigure(figure_str);

            // radius
            double radius = testJson["radius"].toDouble();

            QJsonObject centerObj = testJson["center"].toObject();
            QPoint center = parseCenter(centerObj);

            figure_t resulting_figure = { .algorithm = method, .type = figure, \
                .center = center, .ra = radius, .rb = radius, .color = Qt::black };

            tests << Test(name, desc, resulting_figure, true);
        }
    }
    return tests;
}

algorithm_t TestParser::parseMethod(QString &method)
{
    if (method == "standard")
        return STANDART; // others to be added for other tests...
}

figure_type_t TestParser::parseFigure(QString &figure)
{
    if (figure == "ellipse")
        return ELLIPSE; // others to be added for other tests...
}

QPoint TestParser::parseCenter(QJsonObject &json)
{
    return QPoint(json["x"].toInt(), json["y"].toInt());
}
