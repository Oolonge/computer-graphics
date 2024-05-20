#include "mainwindow.h"
#include "requests.h"
#include "ui_mainwindow.h"
#include "table.h"
#include <QColorDialog>
#include <QMessageBox>
#include <QWheelEvent>
#include <QPolygon>

void MainWindow::on_tableWidget_cellClicked(int row)
{
    point p;
    p.x = ui->tableWidget->item(row, 0)->text().toDouble();
    p.y = ui->tableWidget->item(row, 1)->text().toDouble();
    request req;
    req.data = data;
    req.scene = scene;
    req.view = ui->graphicsView;
    req.hole_figure_flag = true;
    req.p = p;
    req.oper = SELECT_POINT;
    request_handle(req);
}

void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item) // отмену добавить
{
    int row = ui->tableWidget->row(item);
    bool flag_x, flag_y;
    int x = ui->tableWidget->item(row, 0)->text().toInt(&flag_x);
    int y = ui->tableWidget->item(row, 1)->text().toInt(&flag_y);
    int n_f = ui->tableWidget->item(row, 2)->text().toInt();
    int n_h = ui->tableWidget->item(row, 3)->text().toInt();
    size_t i = (size_t) ui->tableWidget->item(row, 4)->text().toInt();
    point old_p;
    if (n_h == -1)
        old_p = data.figures[n_f].main_figure[i];
    else
        old_p = data.figures[n_f].holes[n_h].points[i];

    if (!flag_x)
    {
        error_message("Координата Х должна быть целым числом");
        ui->tableWidget->blockSignals(true);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(old_p.x)));
        ui->centralwidget->blockSignals(false);
    }
    else if (!flag_y)
    {
        error_message("Координата Y должна быть целым числом");
        ui->tableWidget->blockSignals(true);
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(old_p.y)));
        ui->centralwidget->blockSignals(false);
    }
    else
    {
        point p = {x, y};
        request req;
        req.oper = CHANGE_POINT;
        req.data = data;
        req.indexes_data = {n_f, n_h, i};
        req.table = ui->tableWidget;
        req.p = p;
        req.scene = scene;
        req.view = ui->graphicsView;
        int rc = request_handle(req);
        if (rc)
        {
            error_message("Такая точка существует");
            ui->tableWidget->blockSignals(true);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(old_p.x)));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(old_p.y)));
            ui->centralwidget->blockSignals(false);
        }
        else
        {
            content *c = new content;
            copy(&c, &data);
            cancel.push(*c);
            ui->pushButton_cancel->setEnabled(true);
            data = req.data;
        }
    }
}

void MainWindow::on_pushButton_del_point_clicked()
{
    content *c = new content;
    copy(&c, &data);
    cancel.push(*c);
    ui->pushButton_cancel->setEnabled(true);
    QTableWidgetItem *cur_item = ui->tableWidget->currentItem();
    if (cur_item)
    {
        int row = ui->tableWidget->row(cur_item);
        int n_f = ui->tableWidget->item(row, 2)->text().toInt();
        int n_h = ui->tableWidget->item(row, 3)->text().toInt();
        size_t i = (size_t) ui->tableWidget->item(row, 4)->text().toInt();
        request req;
        req.data = data;
        req.indexes_data = {n_f, n_h, i};
        req.table = ui->tableWidget;
        req.scene = scene;
        req.view = ui->graphicsView;
        req.oper = DELETE_POINT;
        request_handle(req);
        data = req.data;
    }
    else
        error_message("Сначала выберите точку");
}
