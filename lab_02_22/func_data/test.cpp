#include "test.h"

Test::Test() {}

Test::Test(QString name, QString desc, QString filename, \
           bool is_scale, bool is_turn, bool is_move, \
           scale sc, turn tr, move mv)
    : name_(name), desc_(desc), filename_(filename), is_scale_(is_scale), is_turn_(is_turn), is_move_(is_move), sc_(sc), tr_(tr), mv_(mv){}

Test::Test(QString name, QString desc) : name_(name), desc_(desc) {}

QString Test::name() const { return this->name_; }

QString Test::desc() const { return this->desc_; }

QString Test::filename() const { return this->filename_; }

scale Test::get_scale() const { return this->sc_; }

turn Test::get_turn() const { return this->tr_; }

move Test::get_move() const { return this->mv_; }

bool Test::isEmpty() { return this->name_.isEmpty() && this->desc_.isEmpty(); }

QDebug operator<<(QDebug stream, const Test &test)
{
    stream << "Текущий тест: " << test.name() << Qt::endl;
    stream << "Описание: " << test.desc() << Qt::endl;
    stream << "Данные о фигуре в файле: " << test.filename() << Qt::endl;

    return stream;
}
