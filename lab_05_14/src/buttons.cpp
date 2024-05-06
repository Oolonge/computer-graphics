#include "mainwindow.h"
#include "requests.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QMessageBox>
#include <QWheelEvent>
#include <iostream>

// выбор формата вывода
void MainWindow::on_comboBox_activated(int index)
{
    if (index == 1)
        ui->spinBox->setEnabled(true);
    else
        ui->spinBox->setEnabled(false);
}

// замыкание фигуры / отверстия
void MainWindow::on_pushButton_close_clicked()
{
    int n_figures = data.n_figures;
    int n_holes = data.n_holes;
    if (!hole_flag) {
        if (data.figures[n_figures].main_figure.size() >= 3) {
            content* c = new content;
            copy(&c, &data);
            cancel.push(*c);
            ui->pushButton_cancel->setEnabled(true);

            data.figures[n_figures].closed_figure_flag = true;
        } else
            error_message("Для замыкания фигуры недостаточно точек");
    } else {
        if (data.figures[n_figures].holes[n_holes].points.size() >= 3) {
            content* c = new content;
            copy(&c, &data);
            cancel.push(*c);
            ui->pushButton_cancel->setEnabled(true);

            data.figures[n_figures].holes[n_holes].closed_hole_flag = true;
            hole_flag = false;
            ui->pushButton_add_hole->setEnabled(true);

        } else
            error_message("Для замыкания отверстия недостаточно точек");
    }
    request req;
    req.data = data;
    req.scene = scene;
    req.view = ui->graphicsView;
    req.hole_figure_flag = false;
    req.p = { 0, 0 };
    req.oper = DRAW;
    handle_request(req);
}

// добавление отверстия
void MainWindow::on_pushButton_add_hole_clicked()
{
    if (!data.figures[data.n_figures].closed_figure_flag)
        error_message("Фигура не замкнута. Сперва замкните ее");
    else {
        content* c = new content;
        copy(&c, &data);
        cancel.push(*c);
        ui->pushButton_cancel->setEnabled(true);

        hole_flag = true;
        ui->pushButton_add_hole->setEnabled(false);
        data.figures[data.n_figures].holes.push_back({ .closed_hole_flag = false });
        data.n_holes++;
    }
}

// очистка всего экрана
void MainWindow::on_pushButton_clear_clicked()
{
    scene->clear();

    line_color = Qt::black;
    fill_color = QColor("#0ABAB5");
    show_color(line_color, ui->label_lc);
    show_color(fill_color, ui->label_fc);
    data.back_color = back_color;

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
    ui->pushButton_drag_mode->setEnabled(true);
    ui->pushButton_cursor_mode->setEnabled(false);
    hand_flag = false;
    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
}

// сброс масштабирования
void MainWindow::on_pushButton_reset_scale_clicked()
{
    ui->graphicsView->resetTransform();
}

// отмена
void MainWindow::on_pushButton_cancel_clicked()
{
    if (!cancel.empty()) {
        data = cancel.top();
        request req;
        req.data = data;
        req.table = ui->tableWidget;
        req.oper = CANCEL_ACTION;
        req.scene = scene;
        req.view = ui->graphicsView;
        handle_request(req);
        cancel.pop();
    }
    if (cancel.empty())
        ui->pushButton_cancel->setEnabled(false);
}

void MainWindow::on_pushButton_fill_clicked()
{
    int delay = 0;
    if (ui->comboBox->currentIndex() == 1) {
        delay = ui->spinBox->value();
    }
    if (data.figures[0].main_figure.empty()) {
        error_message("Введите больше одной точки");
        return;
    }
    for (size_t i = 0; i < data.figures.size(); i++)
        if (data.figures[i].closed_figure_flag)
            for (size_t j = 0; j < data.figures[i].holes.size(); j++)
                if (!data.figures[i].holes[j].closed_hole_flag) {
                    error_message("Перед заливкой фигура должна быть замкнута");
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
    req.colors_data = { line_color, fill_color };
    handle_request(req);
    content* c = new content;
    copy(&c, &data);
    cancel.push(*c);
    ui->pushButton_cancel->setEnabled(true);
    data = req.data;
    std::string str;
    QString s;
    s += "Заливка многоугольников заняла: ";
    for (size_t i = 0; i < req.time.size() - 1; i++) {
        s += QString::number(req.time[i]);
        s += ", ";
    }
    s += QString::number(req.time[req.time.size() - 1]);
    s += " мкс.";
    ui->statusbar->showMessage(s, 20000);
}

void MainWindow::on_pushButton_drag_mode_clicked()
{
    ui->pushButton_drag_mode->setEnabled(false);
    ui->pushButton_cursor_mode->setEnabled(true);
    hand_flag = true;
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
}

void MainWindow::on_pushButton_cursor_mode_clicked()
{
    ui->pushButton_drag_mode->setEnabled(true);
    ui->pushButton_cursor_mode->setEnabled(false);
    hand_flag = false;
    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
    ui->graphicsView->resetTransform();
}
