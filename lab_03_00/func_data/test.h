#ifndef TEST_H
#define TEST_H

#include <QColor>
#include <QDebug>
#include <QList>
#include <QString>
#include <QPoint>
#include <QFile>
#include "consts.h"

class Test {
public:
    Test();
    Test(QString name, QString desc, method_t method, line_t line, bool is_full = true);
    Test(QString name, QString desc, bool is_full = false);
    bool isEmpty();

    QString name() const;
    QString desc() const;
    method_t method() const;
    line_t line() const;
    bool is_full() const;

private:
    QString name_;
    QString desc_;
    method_t method_;
    line_t line_;
    bool full_test_;
};
QDebug operator<<(QDebug stream, const Test &test);

#endif // TEST_H
