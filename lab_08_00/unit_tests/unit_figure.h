#ifndef UNIT_FIGURE_H
#define UNIT_FIGURE_H

#include "figure.h"
#include <QTest>

class TestFigure : public QObject
{
    Q_OBJECT
public:
    explicit TestFigure(QObject *parent = 0);

private slots:
    void initTestCase()
    { qDebug("called before everything else"); }
    void signTestPos(); //int sign(int num)
    void signTestNeg(); //int sign(int num)
    void signTestZero(); //int sign(int num)
    void cleanupTestCase()
    { qDebug("called after all the tests"); }
};


#endif // UNIT_FIGURE_H
