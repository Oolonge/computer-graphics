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

point parsePoint(QJsonObject &json)
{
    point pnt = { .x = json["x"].toInt(), .y = json["y"].toInt() };
    return pnt;
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

            // lines parser
            QJsonObject point_1_obj = testJson["point_1"].toObject();
            point point_1 = parsePoint(point_1_obj);

            QJsonObject point_2_obj = testJson["point_2"].toObject();
            point point_2 = parsePoint(point_2_obj);

            // cut parser
            QJsonObject cut_1_point_obj = testJson["cut_1"].toObject();
            point cut_1 = parsePoint(cut_1_point_obj);

            QJsonObject cut_2_point_obj = testJson["cut_2"].toObject();
            point cut_2 = parsePoint(cut_2_point_obj);

            figure fig = { .p1 = cut_1, .p2 = cut_2 };

            // QList<point> points;
            // QJsonArray pointsJson = testJson["points"].toArray();
            // for (auto pointRef : pointsJson)
            // {
            //     QJsonObject pointObj = pointRef.toObject();
            //     point pnt = { .x = pointObj["x"].toInt(), .y = pointObj["y"].toInt() };
            //     points.append(pnt);
            // }

            tests << Test(name, desc, point_1, point_2, fig, true);
        }
    }
    return tests;
}
