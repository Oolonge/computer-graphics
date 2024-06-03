#include "unit_tests.h"

int sign(int num)
{
    if (num == 0)
        return 0;
    return (num >= 0) ? 1 : -1;
}

#define CNST 999

TestFigure::TestFigure(QObject *parent) :
    QObject(parent)
{
}

void TestFigure::signTestPos()
{
    QCOMPARE(sign(CNST), 1);
}

void TestFigure::signTestNeg()
{
    QCOMPARE(sign(-CNST), -1);
}

void TestFigure::signTestZero()
{
    QCOMPARE(sign(0), 0);
}
