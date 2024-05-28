#include "test.h"

Test::Test() {}

Test::Test(QString name, QString desc, bool is_full) : name_(name), desc_(desc), full_test_(is_full) {}

Test::Test(QString name, QString desc, point point_1, point point_2, figure cut, bool is_full) : \
            name_(name), desc_(desc), point_1_(point_1), point_2_(point_2), cut_(cut), full_test_(is_full) {}

QString Test::name() const { return this->name_; }

QString Test::desc() const { return this->desc_; }

point Test::point_1() const { return this->point_1_; }

point Test::point_2() const { return this->point_2_; }

figure Test::cut() const { return this->cut_; }

bool Test::isEmpty() { return this->name_.isEmpty() && this->desc_.isEmpty(); }

bool Test::is_full() const { return this->full_test_; }

QDebug operator<<(QDebug stream, const Test &test)
{
    stream << "Текущий тест: " << test.name() << Qt::endl;
    stream << "Описание: " << test.desc() << Qt::endl;

    return stream;
}
