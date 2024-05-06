#include "mainwindow.h"
#include "requests.h"
#include "ui_mainwindow.h"
#include "table.h"
#include <QColorDialog>
#include <QMessageBox>
#include <QWheelEvent>
#include <QPolygon>

// выделение точки
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
    handle_request(req);
}

// удаление точки
void MainWindow::on_pushButton_del_point_clicked()
{
    content* c = new content;
    copy(&c, &data);
    cancel.push(*c);
    ui->pushButton_cancel->setEnabled(true);
    QTableWidgetItem* cur_item = ui->tableWidget->currentItem();
    if (cur_item) {
        int row = ui->tableWidget->row(cur_item);
        int n_f = ui->tableWidget->item(row, 2)->text().toInt();
        int n_h = ui->tableWidget->item(row, 3)->text().toInt();
        size_t i = (size_t)ui->tableWidget->item(row, 4)->text().toInt();
        request req;
        req.data = data;
        req.indexes_data = { n_f, n_h, i };
        req.table = ui->tableWidget;
        req.scene = scene;
        req.view = ui->graphicsView;
        req.oper = DELETE_POINT;
        handle_request(req);
        data = req.data;
    } else
        error_message("Сначала выберите точку");
}

void addRow(const point &p, const int &n_figures, const int &n_holes, const size_t &i, QTableWidget *table)
{
    table->blockSignals(true);
    int cnt = table->rowCount();
    table->insertRow(cnt);
    table->setItem(cnt, 0, new QTableWidgetItem(QString::number(p.x)));
    table->setItem(cnt, 1, new QTableWidgetItem(QString::number(p.y)));
    QTableWidgetItem *item = new QTableWidgetItem(QString::number(n_figures));
    item->setFlags(Qt::ItemIsEnabled);
    table->setItem(cnt, 2, item);
    item = new QTableWidgetItem(QString::number(n_holes));
    item->setFlags(Qt::ItemIsEnabled);
    table->setItem(cnt, 3, item);
    table->setItem(cnt, 4, new QTableWidgetItem(QString::number(i)));
    table->blockSignals(false);
}

int addPoint(const point &p, const colors col, const bool &is_hole, QTableWidget *table, content &data)
{
    size_t i;
    if (!is_hole)
    {
        if (data.figures[data.n_figures].closed_figure_flag)
        {
            data.n_figures++;
            data.n_holes = -1;
            figure f;
            f.fill_color = col.fill;
            f.line_color = col.line;
            f.closed_figure_flag = false;
            data.figures.push_back(f);
        }
        std::vector<point> arr = data.figures[data.n_figures].main_figure;
        for (size_t i = 0; i < arr.size(); i++)
            if (arr[i].x == p.x && arr[i].y == p.y)
                return 1;

        data.figures[data.n_figures].main_figure.push_back(p);
        i = data.figures[data.n_figures].main_figure.size() - 1;
    }
    else
    {
        std::vector<point> arr = data.figures[data.n_figures].holes[data.n_holes].points;
        for (size_t i = 0; i < arr.size(); i++)
            if (arr[i].x == p.x && arr[i].y == p.y)
                return 1;
        QPolygon pol;
        for (size_t i = 0; i < data.figures[data.n_figures].main_figure.size(); i++)
        {
            QPoint point = QPoint(data.figures[data.n_figures].main_figure[i].x, data.figures[data.n_figures].main_figure[i].y);
            pol << point;
        }
        QPoint point = QPoint(data.figures[data.n_figures].main_figure[0].x, data.figures[data.n_figures].main_figure[0].y);
        pol << point;
        bool c = pol.containsPoint(QPoint(p.x, p.y), Qt::OddEvenFill);
        if (!c)
            return 2;
        data.figures[data.n_figures].holes[data.n_holes].points.push_back(p);
        i = data.figures[data.n_figures].holes[data.n_holes].points.size() - 1;
    }

    addRow(p, data.n_figures, data.n_holes, i, table);

    return 0;
}

void rewriteTable(const content &data, QTableWidget *table)
{
    table->clearContents();
    table->setRowCount(0);
    for (size_t i = 0; i < data.figures.size(); i++)
    {
        figure cur_f = data.figures[i];
        for (size_t j = 0; j < cur_f.main_figure.size(); j++)
            addRow(cur_f.main_figure[j], i, -1, j, table);
        for (size_t j = 0; j < cur_f.holes.size(); j++)
            for (size_t k = 0; k < cur_f.holes[j].points.size(); k++)
                addRow(cur_f.holes[j].points[k], i, j, k, table);
    }
}

void delRow(const indexes &ind_data, content &data)
{
    if (ind_data.hole == -1)
    {
        data.figures[ind_data.fig].main_figure.erase(data.figures[ind_data.fig].main_figure.begin() + ind_data.index);
        if (data.figures.size() != 1 && data.figures[ind_data.fig].main_figure.size() == 0)
        {
            data.figures.erase(data.figures.begin() + ind_data.fig);
            data.n_figures--;
        }
        if (data.figures[ind_data.fig].main_figure.size() == 1 || data.figures[ind_data.fig].main_figure.size() == 2)
            data.figures[ind_data.fig].closed_figure_flag = false;
    }
    else
    {
        data.figures[ind_data.fig].holes[ind_data.hole].points.erase(data.figures[ind_data.fig].holes[ind_data.hole].points.begin() + ind_data.index);
        if (data.figures[ind_data.fig].holes.size() != 1 && data.figures[ind_data.fig].holes[ind_data.hole].points.size() == 0)
        {
            data.figures[ind_data.fig].holes.erase(data.figures[ind_data.fig].holes.begin() + ind_data.hole);
            if (ind_data.fig == (int) (data.figures.size() - 1))
                data.n_holes--;
        }
        if (data.figures[ind_data.fig].holes[ind_data.hole].points.size() == 1 || data.figures[ind_data.fig].holes[ind_data.hole].points.size() == 2)
            data.figures[ind_data.fig].holes[ind_data.hole].closed_hole_flag = false;
    }
}

int changePoint(const indexes &ind, const point &p, content &data)
{
    if (ind.hole == -1)
    {
        std::vector<point> arr = data.figures[data.n_figures].main_figure;
        for (size_t i = 0; i < arr.size(); i++)
            if (arr[i].x == p.x && arr[i].y == p.y)
                return 1;
        data.figures[ind.fig].main_figure[ind.index] = p;
    }
    else
    {
        std::vector<point> arr = data.figures[data.n_figures].holes[data.n_holes].points;
        for (size_t i = 0; i < arr.size(); i++)
            if (arr[i].x == p.x && arr[i].y == p.y)
                return 1;
        data.figures[ind.fig].holes[ind.hole].points[ind.index] = p;
    }

    return 0;
}
