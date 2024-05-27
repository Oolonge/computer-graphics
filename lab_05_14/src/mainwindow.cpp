#include "mainwindow.h"
#include "requests.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QMessageBox>
#include <QWheelEvent>
#include <iostream>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    // ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->viewport()->installEventFilter(this);

    // temporary disable buttons
    ui->pushButton_cancel->setEnabled(false);
    ui->spinBox->setEnabled(false);

    // color setup
    show_color(fill_color, ui->label_fc);
    show_color(line_color, ui->label_lc);
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
    ui->pushButton_drag_mode->setToolTip("Режим масштабирования");
}

MainWindow::MainWindow(Test test, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    // ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->viewport()->installEventFilter(this);

    ui->graphicsView->setBackgroundBrush(back_color);

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


MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    cancel = std::stack<content>();
}

// func tests
void MainWindow::populateTestData(Test test)
{
    // qDebug() << "populateTestData called";
    // if (!test.is_full())
    //     return;
    // qDebug() << "before cycle";
    for (point pnt : test.point_vector())
    {
        // qDebug() << "x: " << pnt.x << " " << "y: " << pnt.y;
        addPointNoClick(pnt);
    }

    on_pushButton_close_clicked();
    fill_color = test.fill_color();
    on_pushButton_fill_clicked();

    QRectF sceneRect = scene->sceneRect();
    QSize imageSize(sceneRect.size().toSize());
    QImage image(imageSize, QImage::Format_ARGB32);
    image.fill(Qt::white);

    QPainter painter(&image);
    scene->render(&painter);
    QString filename = QString("/Users/administrator/Desktop/qt/C++/lab_05_14/func_data/pics/%1.png").arg(test.name());
    image.save(filename, "png");

    this->deleteLater();
}

void MainWindow::addPointNoClick(point p)
{
    request req;
    req.data = data;
    req.colors_data = { line_color, fill_color };
    req.hole_figure_flag = hole_flag;
    req.p = p;
    req.scene = scene;
    req.table = ui->tableWidget;
    req.view = ui->graphicsView;
    req.oper = ADD_POINT;
    if (!hand_flag) {
        int rc = handle_request(req);
        if (rc == 1)
            error_message("Такая точка уже введена");
        else if (rc == 2)
            error_message("Точка отверстия находится вне фигуры");
        else if (rc == 0) {
            content* c = new content;
            copy(&c, &data);
            cancel.push(*c);
            ui->pushButton_cancel->setEnabled(true);
            data = req.data;
            req.oper = DRAW;
            req.hole_figure_flag = false;
            handle_request(req);
        }
    }
}

//overrides
bool MainWindow::eventFilter(QObject* object, QEvent* event)
{
    if (event->type() == QEvent::Wheel && object == ui->graphicsView->viewport()) {
        if (hand_flag) {
            QWheelEvent* wheel_event = static_cast<QWheelEvent*>(event);
            ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
            double scale_factor = 1.15;
            if (wheel_event->angleDelta().y() > 0) {
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



void MainWindow::mousePressEvent(QMouseEvent* event)
{
    QRect view = ui->graphicsView->geometry();
    if (view.contains(event->pos())) {
        point p = { event->pos().x() - view.x(), event->pos().y() - view.y() - menuBar()->geometry().height() };
        request req;
        req.data = data;
        req.colors_data = { line_color, fill_color };
        req.hole_figure_flag = hole_flag;
        req.p = p;
        req.scene = scene;
        req.table = ui->tableWidget;
        req.view = ui->graphicsView;
        req.oper = ADD_POINT;
        if (!hand_flag) {
            int rc = handle_request(req);
            if (rc == 1)
                error_message("Такая точка уже введена");
            else if (rc == 2)
                error_message("Точка отверстия находится вне фигуры");
            else if (rc == 0) {
                content* c = new content;
                copy(&c, &data);
                cancel.push(*c);
                ui->pushButton_cancel->setEnabled(true);
                data = req.data;
                req.oper = DRAW;
                req.hole_figure_flag = false;
                handle_request(req);
            }
        }
    }
}

void MainWindow::copy(struct content** a, struct content* b)
{
    (*a)->n_figures = b->n_figures;
    (*a)->n_holes = b->n_holes;
    (*a)->back_color = b->back_color;
    for (size_t i = 0; i < b->figures.size(); i++)
        (*a)->figures.push_back(b->figures[i]);
}

void MainWindow::error_message(QString str)
{
    QMessageBox::critical(NULL, "Ошибка", str);
}
