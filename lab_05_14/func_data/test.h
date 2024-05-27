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
    Test(QString name, QString desc, QColor fill_color, QList<point> point_vector, bool is_full = false);
    bool isEmpty();

    QString name() const;
    QString desc() const;
    QColor fill_color() const;
    QList<point> point_vector() const;

    bool is_full() const;

private:
    QString name_;
    QString desc_;
    QColor fill_color_;
    QList<point> point_vector_;

    bool full_test_;
};
QDebug operator<<(QDebug stream, const Test &test);

#endif // TEST_H
