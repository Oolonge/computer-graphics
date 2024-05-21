#include "mainwindow.h"
#include "requests.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QMessageBox>
#include <QWheelEvent>
#include <iostream>

void MainWindow::show_color(QColor color, QLabel* lab)
{
    QImage im = QImage(lab->geometry().width(), lab->geometry().height(), QImage::Format_RGB32);
    QPainter p(&im);
    p.setBrush(QBrush(color));
    p.setPen(Qt::black);
    QRect rect = QRect(0, 0, lab->geometry().width(), lab->geometry().height());
    p.drawRect(rect);

    QPixmap pixmap = QPixmap::fromImage(im);
    lab->clear();
    lab->setPixmap(pixmap);
}

void MainWindow::color_dialog(QColor& color)
{
    QColorDialog dialog;
    dialog.setCurrentColor(color);
    dialog.show();
    dialog.exec();
    QColor tmp = dialog.selectedColor();
    if (!tmp.isValid())
        error_message("Выберите цвет");
    else
        color = tmp;
}

void MainWindow::on_pushButton_line_color_clicked()
{
    color_dialog(data.line_color);
    show_color(data.line_color, ui->label_lc);
}

void MainWindow::on_pushButton_cut_color_clicked()
{
    color_dialog(data.cut_color);
    show_color(data.cut_color, ui->label_cc);
}

void MainWindow::on_pushButton_visible_line_color_clicked()
{
    color_dialog(data.visible_color);
    show_color(data.visible_color, ui->label_vlc);
}
