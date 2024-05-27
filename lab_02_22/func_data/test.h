#ifndef TEST_H
#define TEST_H

#include <QColor>
#include <QDebug>
#include <QList>
#include <QString>
#include <QPoint>
#include <QFile>
#include "operations.h"

class Test {
public:
    Test();
    Test(QString name, QString desc, QString filename, \
         bool is_scale, bool is_turn, bool is_move, \
         scale sc, turn tr, move mv);
    Test(QString name, QString desc);
    QString name() const;
    QString desc() const;
    QString filename() const;

    scale get_scale() const;
    turn get_turn() const;
    move get_move() const;

    bool isEmpty();

    bool is_scale_ = false, is_turn_ = false, is_move_ = false;

private:
    QString name_;
    QString desc_;
    QString filename_;

    scale sc_;
    turn tr_;
    move mv_;
};
QDebug operator<<(QDebug stream, const Test &test);

#endif // TEST_H
