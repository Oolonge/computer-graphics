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
    method_t method;
    line_t line;

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

            // point start
            QJsonObject startObj = testJson["start"].toObject();

            // point end
            QJsonObject endObj = testJson["end"].toObject();

            line = parseLine(startObj, endObj, method);

            tests << Test(name, desc, method, line);
        }
    }
    return tests;
}

method_t TestParser::parseMethod(QString &method)
{
    if (method == "standard")
        return STANDART; // others to be added for other tests...
}

line_t TestParser::parseLine(QJsonObject &startJson, QJsonObject &endJson, method_t &method)
{
    QPoint start = QPoint(startJson["x"].toInt(), startJson["y"].toInt());
    QPoint end = QPoint(endJson["x"].toInt(), endJson["y"].toInt());
    QColor color = Qt::black;
    line_t line = { .start = start, .end = end, .color = color, .method = method };
    return line;
}
