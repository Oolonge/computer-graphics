#include "../inc/taskpopup.h"
#include "ui_taskpopup.h"

TaskPopup::TaskPopup(QWidget *parent) : QDialog(parent), ui(new Ui::TaskPopup) {
  ui->setupUi(this);
  connect(ui->closeButton, SIGNAL(clicked(bool)), this,
          SLOT(onCloseButtonClicked()));
  ui->label->setText(
      "На плоскости дано множество точек.\n\nНайти такой треугольник с "
      "вершинами\nв этих точках, у которого максимальная\nпо длинне "
      "биссектриса минимальна\n\nВывести картинку в графическом виде.");
}

TaskPopup::~TaskPopup() { delete ui; }

void TaskPopup::onCloseButtonClicked() { this->close(); }
