#include "test.h"

Test::Test() {}

Test::Test(QString name, QString desc, method_t method, line_t line, bool is_full) : \
    name_(name), desc_(desc), method_(method), line_(line), full_test_(is_full) {}

Test::Test(QString name, QString desc, bool is_full) : name_(name), desc_(desc), full_test_(is_full) {}

QString Test::name() const { return this->name_; }

QString Test::desc() const { return this->desc_; }

method_t Test::method() const { return this->method_; }

line_t Test::line() const { return this->line_; }

bool Test::isEmpty() { return this->name_.isEmpty() && this->desc_.isEmpty(); }

bool Test::is_full() const { return this->full_test_; }

QDebug operator<<(QDebug stream, const Test &test)
{
    stream << "Текущий тест: " << test.name() << Qt::endl;
    stream << "Описание: " << test.desc() << Qt::endl;
    // stream << "Данные о фигуре в файле: " << test.filename() << Qt::endl;

    return stream;
}
