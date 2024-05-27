#include "test.h"

Test::Test() {}

Test::Test(QString name, QString desc, bool is_full) : name_(name), desc_(desc), full_test_(is_full) {}

Test::Test(QString name, QString desc, QColor fill_color, QList<point> point_vector, bool is_full) : \
    name_(name), desc_(desc), fill_color_(fill_color), point_vector_(point_vector), full_test_(is_full) {}

QString Test::name() const { return this->name_; }

QString Test::desc() const { return this->desc_; }

QColor Test::fill_color() const { return this->fill_color_; }

QList<point> Test::point_vector() const { return this->point_vector_; }

bool Test::isEmpty() { return this->name_.isEmpty() && this->desc_.isEmpty() && this->point_vector_.isEmpty(); }

bool Test::is_full() const { return this->full_test_; }

QDebug operator<<(QDebug stream, const Test &test)
{
    stream << "Текущий тест: " << test.name() << Qt::endl;
    stream << "Описание: " << test.desc() << Qt::endl;

    return stream;
}
