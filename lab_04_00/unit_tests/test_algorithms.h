#ifndef TEST_ALGORITHMS_H
#define TEST_ALGORITHMS_H

#include <QTest>
#include "algorithms.h"
#include "../func_data/test.h"

class TestAlgorithms : public QObject
{
    Q_OBJECT
public:
    explicit TestAlgorithms(QObject *parent = 0);

private slots:
    void initTestCase()
    { qDebug("called before everything else"); }
    void signTestNeg(); //int sign(double x);
    void signTestPos();
    void cleanupTestCase()
    { qDebug("called after all the tests"); }
};

#endif // TEST_ALGORITHMS_H
