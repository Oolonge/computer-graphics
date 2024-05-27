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
    Test(QString name, QString desc, figure_t figure, bool is_full);
    Test(QString name, QString desc, bool is_full = false);
    bool isEmpty();

    QString name() const;
    QString desc() const;
    figure_t figure() const;

    bool is_full() const;

private:
    QString name_;
    QString desc_;
    figure_t figure_;
    bool full_test_;
};
QDebug operator<<(QDebug stream, const Test &test);

#endif // TEST_H
