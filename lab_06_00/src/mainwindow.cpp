#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QColorDialog>
#include <QWheelEvent>
#include "requests.h"
#include <iostream>
//#include "drawing.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // scene related
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->viewport()->installEventFilter(this);

    // temporary disable buttons
    ui->pushButton_cancel->setEnabled(false);
    ui->spinBox->setEnabled(false);

    // color setup
    show_color(line_color, ui->label_lc);
    show_color(fill_color, ui->label_fc);
    ui->graphicsView->setBackgroundBrush(back_color);

    // table widget data
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "x" << "y" << "№ф" << "№о" << "i");
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget->setColumnHidden(4, true);

    data.n_figures = 0;
    data.n_holes = -1;

    figure f;
    f.fill_color = fill_color;
    f.line_color = line_color;
    f.closed_figure_flag = false;
    data.figures.push_back(f);
    data.back_color = back_color;
    data.figures[data.n_figures].line_color = line_color;
    data.figures[data.n_figures].fill_color = fill_color;

    ui->pushButton_cursor_mode->setEnabled(false);

    // tips popup
    ui->pushButton_reset_scale->setToolTip("Ресет масштабирования");
    ui->pushButton_cursor_mode->setToolTip("Режим ввода точек");
    ui->pushButton_hand_mode->setToolTip("Режим масштабирования");
}

MainWindow::MainWindow(Test test, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // scene related
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->viewport()->installEventFilter(this);

    data.n_figures = 0;
    data.n_holes = -1;

    figure f;
    f.fill_color = fill_color;
    f.line_color = line_color;
    f.closed_figure_flag = false;
    data.figures.push_back(f);
    data.back_color = back_color;
    data.figures[data.n_figures].line_color = line_color;
    data.figures[data.n_figures].fill_color = fill_color;

    if (!test.isEmpty())
    {
        this->populateTestData(test);
    }
}

void MainWindow::populateTestData(Test test)
{
    if (!test.is_full())
        return;

    for (point pnt : test.point_vector())
    {
        putPointNoClick(pnt);
    }

    on_pushButton_close_clicked();
    seed_point_flag = true;
    fill_color = test.fill_color();
    putPointNoClick(test.seed_point());
    on_pushButton_fill_clicked();

    QRectF sceneRect = scene->sceneRect();
    QSize imageSize(sceneRect.size().toSize());
    QImage image(imageSize, QImage::Format_ARGB32);
    image.fill(Qt::white);

    QPainter painter(&image);
    scene->render(&painter);
    QString filename = QString("/Users/administrator/Desktop/qt/C++/lab_06_00/func_data/pics/%1.png").arg(test.name());
    image.save(filename, "png");

    this->deleteLater();
}

void MainWindow::putPointNoClick(point p)
{
    request req;
    req.data = data;
    req.colors_data = {line_color, fill_color};
    req.hole_figure_flag = hole_flag;
    req.p = p;
    req.scene = scene;
    req.table = ui->tableWidget;
    req.view = ui->graphicsView;
    req.oper = ADD_POINT;
    if (seed_point_flag) {
        content *c = new content;
        copy(&c, &data);
        cancel.push(*c);
        ui->pushButton_cancel->setEnabled(true);
        seed_point_flag = false;
        ui->pushButton_seed_point_click->setEnabled(true);
        ui->lineEdit_seed_point_x->setText(QString::number(p.x));
        ui->lineEdit_seed_point_y->setText(QString::number(p.y));
        data.seed_point = p;
        data.back_color = fill_color;
        req.data = data;
        req.oper = DRAW;
        req.hole_figure_flag = false;
        request_handle(req);
    }
    else if (!hand_flag && !seed_point_flag)
    {
        int rc = request_handle(req);
        if (rc == 1)
            error_message("Такая точка уже введена");
        else if (rc == 2)
            error_message("Точка отверстия находится вне фигуры");
        else if (rc == 0)
        {
            content *c = new content;
            copy(&c, &data);
            cancel.push(*c);
            ui->pushButton_cancel->setEnabled(true);
            data = req.data;
            req.oper = DRAW;
            req.hole_figure_flag = false;
            request_handle(req);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    cancel = std::stack <content>();
}

void MainWindow::copy(struct content** a, struct content* b)
{
    (*a)->seed_point = b->seed_point;
    (*a)->n_figures = b->n_figures;
    (*a)->n_holes = b->n_holes;
    (*a)->back_color = b->back_color;
    for (size_t i = 0; i < b->figures.size(); i++)
        (*a)->figures.push_back(b->figures[i]);
}

// overrides
bool MainWindow::eventFilter(QObject* object, QEvent* event)
{
    if (event->type() == QEvent::Wheel && object == ui->graphicsView->viewport())
    {
        if (hand_flag) {
            QWheelEvent *wheel_event = static_cast<QWheelEvent *>(event);
            ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
            double scale_factor = 1.15;
            if (wheel_event->angleDelta().y() > 0)
            {
                count++;
                ui->graphicsView->scale(scale_factor, scale_factor);
            } else if (count > 0) {
                count--;
                ui->graphicsView->scale(1 / scale_factor, 1 / scale_factor);
            }
        }
        return true;
    }
    return false;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QRect view = ui->graphicsView->geometry();
    if (view.contains(event->pos())) {
        point p = {event->pos().x() - view.x(), event->pos().y() - view.y() - menuBar()->geometry().height()};
        request req;
        req.data = data;
        req.colors_data = {line_color, fill_color};
        req.hole_figure_flag = hole_flag;
        req.p = p;
        req.scene = scene;
        req.table = ui->tableWidget;
        req.view = ui->graphicsView;
        req.oper = ADD_POINT;
        if (seed_point_flag) {
            content *c = new content;
            copy(&c, &data);
            cancel.push(*c);
            ui->pushButton_cancel->setEnabled(true);
            seed_point_flag = false;
            ui->pushButton_seed_point_click->setEnabled(true);
            ui->lineEdit_seed_point_x->setText(QString::number(p.x));
            ui->lineEdit_seed_point_y->setText(QString::number(p.y));
            data.seed_point = p;
            data.back_color = fill_color;
            req.data = data;
            req.oper = DRAW;
            req.hole_figure_flag = false;
            request_handle(req);
        }
        else if (!hand_flag && !seed_point_flag)
        {
            int rc = request_handle(req);
            if (rc == 1)
                error_message("Такая точка уже введена");
            else if (rc == 2)
                error_message("Точка отверстия находится вне фигуры");
            else if (rc == 0)
            {
                content *c = new content;
                copy(&c, &data);
                cancel.push(*c);
                ui->pushButton_cancel->setEnabled(true);
                data = req.data;
                req.oper = DRAW;
                req.hole_figure_flag = false;
                request_handle(req);
            }
        }
    }
}

void MainWindow::error_message(QString str)
{
    QMessageBox::critical(NULL, "Ошибка", str);
}
