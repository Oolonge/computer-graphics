#ifndef TEST_H
#define TEST_H

#include <QColor>
#include <QDebug>
#include <QList>
#include <QString>
#include <QPoint>
#include <QFile>
#include "structures.h"

class Test {
public:
    Test();
    Test(QString name, QString desc, bool is_full = false);
    Test(QString name, QString desc, point point_1, point point_2, figure cut, bool is_full = false);
    bool isEmpty();

    QString name() const;
    QString desc() const;
    point point_1() const;
    point point_2() const;
    figure cut() const;

    bool is_full() const;

private:
    QString name_;
    QString desc_;
    point point_1_;
    point point_2_;
    figure cut_;

    bool full_test_;
};
QDebug operator<<(QDebug stream, const Test &test);

#endif // TEST_H
