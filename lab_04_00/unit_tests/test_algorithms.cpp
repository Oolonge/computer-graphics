#include "test_algorithms.h"

TestAlgorithms::TestAlgorithms(QObject *parent) :
    QObject(parent)
{
}

void TestAlgorithms::signTestNeg()
{
    QCOMPARE(sign(-999), -1);
}

void TestAlgorithms::signTestPos()
{
    QCOMPARE(sign(999), 1);
}
