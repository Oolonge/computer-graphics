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

            // fill_color
            QColor fill_color = testJson["fill_color"].toString();

            // seed point
            QJsonObject seed_point_obj = testJson["seed_point"].toObject();
            point seed_point = parsePoint(seed_point_obj);

            QList<point> points;
            QJsonArray pointsJson = testJson["points"].toArray();
            for (auto pointRef : pointsJson)
            {
                QJsonObject pointObj = pointRef.toObject();
                point pnt = { .x = pointObj["x"].toInt(), .y = pointObj["y"].toInt() };
                points.append(pnt);
            }
            tests << Test(name, desc, fill_color, points, seed_point, true);
        }
    }
    return tests;
}
