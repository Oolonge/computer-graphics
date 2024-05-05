#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QColor>
#include <QMessageBox>
#include <QWheelEvent>
#include <iostream>
#include <QTimer>
#include <QDrag>
#include <QtGlobal>
#include "request_handler.h"

// выбор цвета фона
void MainWindow::on_pushButton_back_color_clicked()
{
    QColorDialog dialog;
    dialog.setCurrentColor(data.back_color);
    dialog.show();
    dialog.exec();
    QColor color = dialog.selectedColor();
    if (!color.isValid())
        errorMessage("Выберите цвет");
    else
        back_color = color;
    displayColor(back_color, ui->label_bc);
}

// выбор цвета линий
void MainWindow::on_pushButton_line_color_clicked()
{
    QColorDialog dialog;
    dialog.setCurrentColor(line_color);
    dialog.show();
    dialog.exec();
    QColor color = dialog.selectedColor();
    if (!color.isValid())
        errorMessage("Выберите цвет");
    else
        line_color = color;
    displayColor(line_color, ui->label_lc);
}

// функция очистки всего холста
void MainWindow::on_pushButton_clear_clicked()
{
    data.back_color = Qt::white;
    line_color = Qt::black;
    displayColor(data.back_color, ui->label_bc);
    displayColor(line_color, ui->label_lc);
    data.figures.clear();
    data.spectrums.clear();
    cancel = std::stack<content_t>();
    ui->graphicsView->resetTransform();
    request req;
    req.scene = scene;
    req.gv = ui->graphicsView;
    req.operation = DRAW_ALL;
    req.data = data;
    handle_request(req);
    ui->pushButton_cancel->setEnabled(false);
}

// функция отмены действия
void MainWindow::on_pushButton_cancel_clicked()
{
    if (!cancel.empty())
    {
        data = cancel.top();
        request req;
        req.data = data;
        req.operation = DRAW_ALL;
        req.scene = scene;
        req.gv = ui->graphicsView;
        handle_request(req);
        cancel.pop();
    }
    if (cancel.empty())
        ui->pushButton_cancel->setEnabled(false);
}

// сброс масштабирования
void MainWindow::on_pushButton_reset_scale_clicked()
{
    ui->graphicsView->resetTransform();
}

// выбор фигуры
void MainWindow::on_comboBox_figure_activated(int index)
{
    if (index == 1)
    {
        ui->lineEdit_spectrum_r2->setDisabled(false);
        ui->lineEdit_figure_r2->setDisabled(false);
        ui->lineEdit_spectrum_dr2->setDisabled(false);
    }
    else
    {
        ui->lineEdit_spectrum_r2->setDisabled(true);
        ui->lineEdit_figure_r2->setDisabled(true);
        ui->lineEdit_spectrum_dr2->setDisabled(true);
    }
}

// рисование одной фигуры
void MainWindow::on_pushButton_figure_clicked()
{
    QString str_x = ui->lineEdit_figure_x->text();
    QString str_y = ui->lineEdit_figure_y->text();
    QString str_r1 = ui->lineEdit_figure_r1->text();
    QString str_r2 = ui->lineEdit_figure_r2->text();

    figure_type_t type = (figure_type_t) ui->comboBox_figure->currentIndex();

    if (!str_x.length() || !str_y.length() || !str_r1.length() || (type == ELLIPSE && !str_r2.length()))
        errorMessage("Ошибка ввода: неполный или пустой ввод");
    else
    {
        bool flag_x, flag_y, flag_r1, flag_r2;
        int x, y, r1, r2;
        x = str_x.toInt(&flag_x);
        y = str_y.toInt(&flag_y);
        r1 = str_r1.toInt(&flag_r1);
        r2 = str_r2.toInt(&flag_r2);

        if (!flag_x || !flag_y || !flag_r1 || (type == ELLIPSE && !flag_r2))
            errorMessage("Ошибка ввода: некорректный ввод");
        else
        {
            content_t *c = new content_t;
            copy(&c, &data);
            cancel.push(*c);
            ui->pushButton_cancel->setEnabled(true);
            QPoint center = QPoint(x, y);
            figure_t figure;
            figure.center = center;
            figure.type = type;
            figure.color = line_color;
            figure.algorithm = (algorithm_t) ui->comboBox_method->currentIndex();
            figure.ra = r1;
            if (type == ELLIPSE)
                figure.rb = r2;
            data.figures.push_back(figure);
            data.back_color = back_color;
            ui->graphicsView->setBackgroundBrush(back_color);

            request req;
            req.operation = DRAW_CIRCLE;
            if (type == ELLIPSE)
                req.operation = DRAW_ELLIPSE;
            req.figure = figure;
            req.scene = scene;
            req.gv = ui->graphicsView;
            handle_request(req);
        }
    }
}

// рисование одного спектра
void MainWindow::on_pushButton_spectrum_clicked()
{
    QString str_x = ui->lineEdit_spectrum_x->text();
    QString str_y = ui->lineEdit_spectrum_y->text();
    QString str_r1 = ui->lineEdit_spectrum_r1->text();
    QString str_r2 = ui->lineEdit_spectrum_r2->text();
    QString str_dr1 = ui->lineEdit_spectrum_dr1->text();
    QString str_dr2 = ui->lineEdit_spectrum_dr2->text();
    QString str_n = ui->lineEdit_spectrum_n->text();


    figure_type_t type = (figure_type_t) ui->comboBox_figure->currentIndex();

    if (!str_x.length() || !str_y.length() || !str_n.length() || !str_r1.length() || !str_dr1.length() || (type == ELLIPSE && (!str_r2.length() || !str_dr2.length())))
        errorMessage("Ошибка ввода: неполный или пустой ввод");
    else
    {
        bool flag_x, flag_y, flag_r1, flag_r2, flag_dr1, flag_dr2, flag_n;
        int x, y, r1, r2, dr1, dr2;
        int n;
        x = str_x.toInt(&flag_x);
        y = str_y.toInt(&flag_y);
        r1 = str_r1.toInt(&flag_r1);
        r2 = str_r2.toInt(&flag_r2);
        dr1 = str_dr1.toInt(&flag_dr1);
        dr2 = str_dr2.toInt(&flag_dr2);
        n = str_n.toInt(&flag_n);

        if (!flag_x || !flag_y || !flag_n || !flag_dr1 || !flag_r1 || (type == ELLIPSE && (!flag_r2 || !flag_dr2)))
            errorMessage("Ошибка ввода: некорректный ввод");
        else
        {
            content_t *c = new content_t;
            copy(&c, &data);
            cancel.push(*c);
            ui->pushButton_cancel->setEnabled(true);
            QPoint center = QPoint(x, y);
            spectrum_t spectrum;
            spectrum.center = center;
            spectrum.type = type;
            spectrum.algorithm = (algorithm_t) ui->comboBox_method->currentIndex();
            spectrum.color = line_color;
            spectrum.dra = dr1;
            spectrum.n = n;
            spectrum.ra = r1;
            if (type == ELLIPSE)
            {
                spectrum.drb = dr2;
                spectrum.rb = r2;
            }
            data.spectrums.push_back(spectrum);
            data.back_color = back_color;
            ui->graphicsView->setBackgroundBrush(back_color);
            request req;
            req.operation = DRAW_CIRCLE_SPECTRUM;
            if (type == ELLIPSE)
                req.operation = DRAW_ELLIPSE_SPECTRUM;
            req.scene = scene;
            req.gv = ui->graphicsView;
            req.spectrum = spectrum;
            handle_request(req);
        }
    }
}
