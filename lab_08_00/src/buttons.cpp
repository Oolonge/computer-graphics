#include "mainwindow.h"
#include "requests.h"
#include "ui_mainwindow.h"
#include "figure.h"
#include <QColorDialog>
#include <QMessageBox>
#include <QWheelEvent>
#include <iostream>

void MainWindow::on_pushButton_add_point_clicked()
{
    QString str_x = ui->lineEdit_x->text();
    QString str_y = ui->lineEdit_y->text();

    if (str_x.length() == 0 && str_y.length() == 0)
        error_message("Введите коориднаты точки");
    else if (str_x.length() == 0)
        error_message("Ошибка ввода! введите координату Х");
    else if (str_y.length() == 0)
        error_message("Ошибка ввода! введите координату Y");
    else {
        bool flag_x, flag_y;
        int x, y;
        x = str_x.toInt(&flag_x);
        y = str_y.toInt(&flag_y);

        if (!flag_x)
            error_message("Ошибка ввода! координата Х должна быть числом");
        else if (!flag_y)
            error_message("Ошибка ввода! координата Y должна быть числом");
        else if (x < 0 || y < 0)
            error_message("Ошибка ввода! точка находится за пределами поля");
        else {
            point p = { x, y };
            add_draw_point(p);
        }
    }
}

void MainWindow::on_pushButton_cancel_clicked()
{
    if (!cancel.empty()) {
        data = cancel.top();
        request req;
        req.data = data;
        req.operation = DRAW_ALL;
        req.scene = scene;
        req.view = ui->graphicsView;
        request_handle(req);
        cancel.pop();
        if (!ui->radioButton_cut->isChecked())
            process_flag = not process_flag;
        else {
            if (!data.cut.close_flag)
                process_flag = true;
            else
                process_flag = false;
        }
    }
    if (cancel.empty())
        ui->pushButton_cancel->setEnabled(false);
}

void MainWindow::on_pushButton_clear_clicked()
{
    scene->clear();

    data.cut_color = Qt::blue;
    data.line_color = Qt::black;
    data.visible_color = QColor("#FF0000");

    show_color(data.cut_color, ui->label_cc);
    show_color(data.line_color, ui->label_lc);
    show_color(data.visible_color, ui->label_vlc);

    data.cut.close_flag = false;
    data.cut.points.clear();
    data.cut.lines.clear();
    data.lines.clear();
    data.lines.push_back({});

    cancel = std::stack<content>();
    ui->pushButton_cancel->setEnabled(false);

    ui->graphicsView->resetTransform();
    ui->pushButton_hand_mode->setEnabled(true);
    ui->pushButton_cursor_mode->setEnabled(false);
    hand_flag = false;
    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
}

void MainWindow::on_pushButton_cut_clicked()
{
    if (data.cut.points.empty())
    {
        error_message("Введите отсекатель");
        return;
    }
    if (!data.cut.close_flag)
    {
        error_message("Замкните отсекатель");
        return;
    }
    if (!checkConvex(data.cut) || checkCross(data.cut))
    {
        error_message("Введен некорректный отсекатель");
        return;
    }
    if ((data.lines.size() > 1 && !data.lines[data.lines.size() - 2].is_full())
        || (data.lines.size() == 1 && !data.lines[0].is_full())) {
        error_message("Введите отрезок");
        return;
    }
    request req;
    req.data = data;
    req.operation = CUT;
    req.scene = scene;
    req.view = ui->graphicsView;
    request_handle(req);
}

void MainWindow::on_pushButton_reset_scale_clicked()
{
    ui->graphicsView->resetTransform();
}

void MainWindow::on_pushButton_cursor_mode_clicked()
{
    ui->pushButton_hand_mode->setEnabled(true);
    ui->pushButton_cursor_mode->setEnabled(false);
    hand_flag = false;
    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
    ui->graphicsView->resetTransform();
}

void MainWindow::on_pushButton_hand_mode_clicked()
{
    ui->pushButton_hand_mode->setEnabled(false);
    ui->pushButton_cursor_mode->setEnabled(true);
    hand_flag = true;
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
}

void MainWindow::on_pushButton_close_cut_clicked()
{
    push_cancel();
    process_flag = false;
    data.cut.close_flag = true;
    data.cut.update_lines(data.cut.points[0]);
    request req;
    req.data = data;
    req.scene = scene;
    req.view = ui->graphicsView;
    req.operation = DRAW_ALL;
    request_handle(req);
}
