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

    turn tr;
    scale sc;
    move mv;

    QJsonArray data = this->doc.array();
    for (const auto &jsonValue : data) {
        if (jsonValue.isObject()) {
            QJsonObject testJson = jsonValue.toObject();
            // name
            QString name = testJson["name"].toString();

            // desc
            QString desc = testJson["desc"].toString();

            // filename
            QString filename = testJson["filename"].toString();

            //  parsing actions
            // QList<Action> actions;
            QJsonArray actionsJson = testJson["actions"].toArray();
            for (auto actionRef : actionsJson) {
                QJsonObject action = actionRef.toObject();
                QString actionType = action["type"].toString();

                if (actionType == "turn")
                {
                    tr = parseTurn(action);
                }
                else if (actionType == "scale")
                {
                    sc = parseScale(action);
                }
                else if (actionType == "move")
                {
                    mv = parseMove(action);
                }
            }

            tests << Test(name, desc, filename, true, true, true, sc, tr, mv);
        }
    }
    return tests;
}

scale TestParser::parseScale(QJsonObject &json)
{
    scale sc = { .kx = json["kx"].toDouble(), .ky = json["ky"].toDouble() };
    return sc;
}

turn TestParser::parseTurn(QJsonObject &json)
{
    turn tr = { .ox = json["ox"].toInt(), .oy = json["oy"].toInt() };
    return tr;
}

move TestParser::parseMove(QJsonObject &json)
{
    move mv = { .dx = json["dx"].toInt(), .dy = json["dy"].toInt() };
    return mv;
}

// QPoint TestParser::parsePoint(QJsonObject &json) {
//     return QPoint(json["x"].toInt(), json["y"].toInt());
// }

// QColor TestParser::parseColor(QJsonObject &json) {
//     QColor color;
//     if (json.contains("color")) {
//         color = QColor(json["color"].toString());
//     } else {
//         color = QColor(Qt::black);
//     }
//     return color;
// }
