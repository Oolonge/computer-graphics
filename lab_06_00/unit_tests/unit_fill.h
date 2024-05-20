#ifndef UNIT_FILL_H
#define UNIT_FILL_H

#include "fill.h"
#include <QTest>

class TestFill : public QObject
{
    Q_OBJECT
public:
    explicit TestFill(QObject *parent = 0);

private slots:
    void initTestCase()
    { qDebug("called before everything else"); }
    void compTestPos(); //bool comp(node a1, node a2);
    void compTestNeg();
    void cleanupTestCase()
    { qDebug("called after all the tests"); }
};

#endif // UNIT_FILL_H
