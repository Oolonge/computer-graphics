#include "aboutpopup.h"
#include "ui_aboutpopup.h"

aboutpopup::aboutpopup(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::aboutpopup)
{
    ui->setupUi(this);
    ui->label->setText("Программу разработал студент МГТУ им. Баумана,\nкафедра ИУ7, группа 41Б\nОвчинников Ярослав Романович\n\n\n2024 год");
}

aboutpopup::~aboutpopup()
{
    delete ui;
}
