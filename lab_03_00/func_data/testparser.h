#ifndef TESTPARSER_H
#define TESTPARSER_H

#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include <QPoint>

#include "test.h"

class TestParser {
public:
    TestParser();
    bool loadFromFile(QString filepath);
    QList<Test> tests();

protected:
    QJsonDocument doc;

private:
    method_t parseMethod(QString &method);
    line_t parseLine(QJsonObject &startJson, QJsonObject &endJson, method_t &method);
};

#endif // TESTPARSER_H
