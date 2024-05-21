#include "mainwindow.h"
#include "requests.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QMessageBox>
#include <QWheelEvent>
#include <iostream>

void MainWindow::on_pushButton_addPoint_clicked()
{
    QString str_x = ui->lineEdit_x->text();
    QString str_y = ui->lineEdit_y->text();

    if (str_x.length() == 0 && str_y.length() == 0)
        error_message("Введите коориднаты точки");
    else if (str_x.length() == 0)
        error_message("Ошибка ввода: введите координату Х");
    else if (str_y.length() == 0)
        error_message("Ошибка ввода: введите координату Y");
    else {
        bool flag_x, flag_y;
        int x, y;
        x = str_x.toInt(&flag_x);
        y = str_y.toInt(&flag_y);

        if (!flag_x)
            error_message("Ошибка ввода: координата Х - число");
        else if (!flag_y)
            error_message("Ошибка ввода: координата Y - число");
        else if (x < 0 || y < 0)
            error_message("Ошибка ввода: точка находится за пределами поля");
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
        handle_request(req);
        cancel.pop();
        process_flag = not process_flag;
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

    data.cut = { {}, {} };
    data.lines.clear();
    data.lines.push_back({});

    data.cut_amount = 0;

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
    if (!data.cut.is_full()) {
        error_message("Введите отсекатель");
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
    handle_request(req);
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
