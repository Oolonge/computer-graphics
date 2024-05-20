#include "mainwindow.h"
#include "requests.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QMessageBox>
#include <QWheelEvent>
#include <iostream>

void MainWindow::on_pushButton_reset_scale_clicked()
{
    ui->graphicsView->resetTransform();
}

void MainWindow::on_comboBox_activated(int index)
{
    if (index == 1)
        ui->spinBox->setEnabled(true);
    else
        ui->spinBox->setEnabled(false);
}

void MainWindow::on_pushButton_close_clicked()
{
    int n_figures = data.n_figures;
    int n_holes = data.n_holes;
    if (!hole_flag)
    {
        if (data.figures[n_figures].main_figure.size() >= 3)
        {
            content *c = new content;
            copy(&c, &data);
            cancel.push(*c);
            ui->pushButton_cancel->setEnabled(true);

            data.figures[n_figures].closed_figure_flag = true;
        }
        else
            error_message("Недостаточно точек, чтобы замкнуть фигуру");
    }
    else
    {
        if (data.figures[n_figures].holes[n_holes].points.size() >= 3)
        {
            content *c = new content;
            copy(&c, &data);
            cancel.push(*c);
            ui->pushButton_cancel->setEnabled(true);

            data.figures[n_figures].holes[n_holes].is_closed_hole = true;
            hole_flag = false;
            ui->pushButton_add_hole->setEnabled(true);

        }
        else
            error_message("Недостаточно точек, чтобы замкнуть отверстие");
    }
    request req;
    req.data = data;
    req.scene = scene;
    req.view = ui->graphicsView;
    req.hole_figure_flag = false;
    req.p = {0, 0};
    req.oper = DRAW;
    request_handle(req);
}

void MainWindow::on_pushButton_add_hole_clicked()
{
    if (!data.figures[data.n_figures].closed_figure_flag)
        error_message("Фигура не замкнута. Сперва замкните ее");
    else
    {
        content *c = new content;
        copy(&c, &data);
        cancel.push(*c);
        ui->pushButton_cancel->setEnabled(true);

        hole_flag = true;
        ui->pushButton_add_hole->setEnabled(false);
        data.figures[data.n_figures].holes.push_back({.is_closed_hole = false});
        data.n_holes++;
    }

}

void MainWindow::on_pushButton_clear_clicked()
{
    scene->clear();

    line_color = Qt::black;
    fill_color = QColor("#0ABAB5");
    show_color(line_color, ui->label_lc);
    show_color(fill_color, ui->label_fc);
    data.back_color = back_color;
    data.seed_point.x = Q_QNAN;
    data.seed_point.y = Q_QNAN;
    ui->lineEdit_seed_point_x->setText("");
    ui->lineEdit_seed_point_y->setText("");

    cancel = std::stack<content>();
    ui->pushButton_cancel->setEnabled(false);

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    data.figures.clear();
    data.n_figures = 0;
    data.n_holes = -1;
    figure f;
    f.fill_color = fill_color;
    f.line_color = line_color;
    f.closed_figure_flag = false;
    data.figures.push_back(f);
    data.figures[data.n_figures].line_color = line_color;
    data.figures[data.n_figures].fill_color = fill_color;

    ui->graphicsView->resetTransform();
    ui->pushButton_hand_mode->setEnabled(true);
    ui->pushButton_cursor_mode->setEnabled(false);
    hand_flag = false;
    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
}

void MainWindow::on_pushButton_cancel_clicked()
{
    if (!cancel.empty())
    {
        data = cancel.top();
        if (data.seed_point.x != -2147483648)
            ui->lineEdit_seed_point_x->setText(QString::number(data.seed_point.x));
        else
            ui->lineEdit_seed_point_x->setText("");
        if (data.seed_point.y != -2147483648)
            ui->lineEdit_seed_point_y->setText(QString::number(data.seed_point.y));
        else
            ui->lineEdit_seed_point_y->setText("");
        request req;
        req.data = data;
        req.table = ui->tableWidget;
        req.oper = CANCEL_ACTION;
        req.scene = scene;
        req.view = ui->graphicsView;
        request_handle(req);
        cancel.pop();
    }
    if (cancel.empty())
        ui->pushButton_cancel->setEnabled(false);
}

void MainWindow::on_pushButton_fill_clicked()
{
    int delay = 0;
    if (ui->comboBox->currentIndex() == 1)
    {
        delay = ui->spinBox->value();
    }
    if (data.figures[0].main_figure.empty())
    {
        error_message("Введите хотя бы несколько точек");
        return;
    }
    if (!data.seed_point.x && !data.seed_point.y)
    {
        error_message("Введите затравочную точку");
        return;
    }
    request req;
    std::vector<double> time;
    req.data = data;
    req.time = time;
    req.oper = FILL_AREA;
    req.delay = delay;
    req.scene = scene;
    req.view = ui->graphicsView;
    req.colors_data = {line_color, fill_color};
    int rc = request_handle(req);
    if (rc)
    {
        error_message("Что-то пошло не так. Проверьте входные данные, пожалуйста");
        return;
    }
    content *c = new content;
    copy(&c, &data);
    cancel.push(*c);
    ui->pushButton_cancel->setEnabled(true);
    data = req.data;
    std::string str;
    QString s;
    s += "Время заливки многоульников: ";
    for (size_t i = 0; i < req.time.size() - 1; i++)
    {
        s += QString::number(req.time[i]);
        s += ", ";
    }
    s += QString::number(req.time[req.time.size() - 1]);
    s += " мкс.";
    ui->statusbar->showMessage(s, 20000);
}

void MainWindow::on_pushButton_hand_mode_clicked()
{
    ui->pushButton_hand_mode->setEnabled(false);
    ui->pushButton_cursor_mode->setEnabled(true);
    hand_flag = true;
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
}

void MainWindow::on_pushButton_cursor_mode_clicked()
{
    ui->pushButton_hand_mode->setEnabled(true);
    ui->pushButton_cursor_mode->setEnabled(false);
    hand_flag = false;
    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
    ui->graphicsView->resetTransform();
}

void MainWindow::on_pushButton_seed_point_click_clicked()
{
    seed_point_flag = true;
    ui->pushButton_cursor_mode->setEnabled(false);
    ui->pushButton_hand_mode->setEnabled(true);
    ui->pushButton_seed_point_click->setEnabled(false);
    hand_flag = false;
    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
    ui->graphicsView->resetTransform();

}

void MainWindow::on_pushButton_seed_point_key_clicked()
{
    QString str_x = ui->lineEdit_seed_point_x->text();
    QString str_y = ui->lineEdit_seed_point_y->text();

    if (str_x.length() == 0)
        error_message("Ошибка ввода: введите координату Х затравочной точки");
    else if (str_y.length() == 0)
        error_message("Ошибка ввода: введите координату Y затравочной точки");
    else
    {
        bool flag_x, flag_y;
        int x, y;
        x = str_x.toInt(&flag_x);
        y = str_y.toInt(&flag_y);

        if (!flag_x)
            error_message("Ошибка ввода: координата Х - число");
        else if (!flag_y)
            error_message("Ошибка ввода: координата Y - число");
        else
        {
            content *c = new content;
            copy(&c, &data);
            cancel.push(*c);
            ui->pushButton_cancel->setEnabled(true);
            point p = {x, y};
            request req;
            data.seed_point = p;
            req.data = data;
            req.p = p;
            req.scene = scene;
            req.view = ui->graphicsView;
            req.oper = DRAW;
            req.hole_figure_flag = false;
            request_handle(req);

        }
    }
}
