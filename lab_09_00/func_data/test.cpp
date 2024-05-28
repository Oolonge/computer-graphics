#include "test.h"

Test::Test() {}

Test::Test(QString name, QString desc, bool is_full) : name_(name), desc_(desc), full_test_(is_full) {}

Test::Test(QString name, QString desc, QList<point> figure, QList<point> cutter, bool is_full) : \
    name_(name), desc_(desc), figure_(figure), cutter_(cutter), full_test_(is_full) {}

QString Test::name() const { return this->name_; }

QString Test::desc() const { return this->desc_; }

QList<point> Test::figure() const { return this->figure_; }

QList<point> Test::cutter() const { return this->cutter_; }

bool Test::isEmpty() { return this->name_.isEmpty() && this->desc_.isEmpty(); }

bool Test::is_full() const { return this->full_test_; }

QDebug operator<<(QDebug stream, const Test &test)
{
    stream << "Текущий тест: " << test.name() << Qt::endl;
    stream << "Описание: " << test.desc() << Qt::endl;

    return stream;
}
