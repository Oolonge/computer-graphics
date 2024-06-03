#include "test.h"

Test::Test() {}

Test::Test(QString name, QString desc, bool is_full) : name_(name), desc_(desc), full_test_(is_full) {}

Test::Test(QString name, QString desc, size_t function_index, QList<double> x_border, \
    QList<double> z_border, QList<double> transformation, int scale, bool is_full) :
    name_(name), desc_(desc), function_index_(function_index), x_border_(x_border), z_border_(z_border),\
    transformations_(transformation), scale_coefficient_(scale), full_test_(is_full) {}

QString Test::name() const { return this->name_; }

QString Test::desc() const { return this->desc_; }

size_t Test::function_index() const { return this->function_index_; }

QList<double> Test::x_border() const { return this->x_border_; }

QList<double> Test::z_border() const { return this->z_border_; }

QList<double> Test::transformations() const { return this->transformations_; }

int Test::scale_coefficient() const { return this->scale_coefficient_; }

bool Test::isEmpty() { return this->name_.isEmpty() && this->desc_.isEmpty(); }

bool Test::is_full() const { return this->full_test_; }

QDebug operator<<(QDebug stream, const Test &test)
{
    stream << "Текущий тест: " << test.name() << Qt::endl;
    stream << "Описание: " << test.desc() << Qt::endl;

    return stream;
}
