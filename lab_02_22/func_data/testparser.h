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
    scale parseScale(QJsonObject &json);
    turn parseTurn(QJsonObject &json);
    move parseMove(QJsonObject &json);
};

#endif // TESTPARSER_H
