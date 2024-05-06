#include "unit_fill.h"

// bool comp(node a1, node a2)
// {
//     return a1.x >= a2.x;
// }

// struct node
// {
//     double x;
//     double dx;
//     int dy;
// };

TestFill::TestFill(QObject *parent) :
    QObject(parent)
{
}

void TestFill::compTestNeg()
{
    node a = { .x = 1., .dx = 2., .dy = 3};
    node b = { .x = 2., .dx = 3., .dy = 4};
    QCOMPARE(comp(a, b), false);
}

void TestFill::compTestPos()
{
    node b = { .x = 1., .dx = 2., .dy = 3};
    node a = { .x = 2., .dx = 3., .dy = 4};
    QCOMPARE(comp(a, b), true);
}
