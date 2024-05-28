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
    Test(QString name, QString desc, QList<point> figure, QList<point> cutter, bool is_full = false);
    bool isEmpty();

    QString name() const;
    QString desc() const;
    QList<point> figure() const;
    QList<point> cutter() const;

    bool is_full() const;

private:
    QString name_;
    QString desc_;
    QList<point> figure_;
    QList<point> cutter_;

    bool full_test_;
};
QDebug operator<<(QDebug stream, const Test &test);

#endif // TEST_H
