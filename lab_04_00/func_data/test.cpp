#include "test.h"

Test::Test() {}

Test::Test(QString name, QString desc, figure_t figure, bool is_full) : \
    name_(name), desc_(desc), figure_(figure), full_test_(is_full) {}

Test::Test(QString name, QString desc, bool is_full) : name_(name), \
    desc_(desc), full_test_(is_full) {}

bool Test::isEmpty() { return this->name_.isEmpty() && this->desc_.isEmpty(); }

QString Test::name() const { return this->name_; }

QString Test::desc() const { return this->desc_; }

figure_t Test::figure() const { return this->figure_; }

bool Test::is_full() const { return this->full_test_; }

QDebug operator<<(QDebug stream, const Test &test)
{
    stream << "Текущий тест: " << test.name() << Qt::endl;
    stream << "Описание: " << test.desc() << Qt::endl;

    return stream;
}
