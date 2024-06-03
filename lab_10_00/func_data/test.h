#ifndef TEST_H
#define TEST_H

#include <QColor>
#include <QDebug>
#include <QList>
#include <QString>
#include <QPoint>
#include <QFile>

class Test {
public:
    Test();
    Test(QString name, QString desc, size_t function_index, QList<double> x_border, QList<double> z_border, QList<double> transformation, int scale, bool is_full = true);
    Test(QString name, QString desc, bool is_full = false);

    bool isEmpty();

    QString name() const;
    QString desc() const;
    size_t function_index() const;
    QList<double> x_border() const;
    QList<double> z_border() const;
    QList<double> transformations() const;
    int scale_coefficient() const;

    bool is_full() const;

private:
    QString name_;
    QString desc_;
    size_t function_index_;
    QList<double> x_border_;
    QList<double> z_border_;
    QList<double> transformations_;
    int scale_coefficient_;

    bool full_test_;
};
QDebug operator<<(QDebug stream, const Test &test);

#endif // TEST_H
