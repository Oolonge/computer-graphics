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
    Test(QString name, QString desc, line segment, QList<point> cutter, bool is_full = false);
    bool isEmpty();

    QString name() const;
    QString desc() const;
    line segment() const;
    QList<point> cutter() const;

    bool is_full() const;

private:
    QString name_;
    QString desc_;
    line segment_;
    QList<point> cutter_;

    bool full_test_;
};
QDebug operator<<(QDebug stream, const Test &test);

#endif // TEST_H
