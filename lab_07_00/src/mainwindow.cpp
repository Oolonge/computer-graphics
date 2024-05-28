#include "mainwindow.h"
#include "requests.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QWidget>
#include <cmath>

#include <iostream>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // initial colors;
    data.cut_color = Qt::blue;
    data.line_color = Qt::black;
    data.visible_color = QColor("#FF0000");

    show_color(data.cut_color, ui->label_cc);
    show_color(data.visible_color, ui->label_vlc);
    show_color(data.line_color, ui->label_lc);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->viewport()->installEventFilter(this);

    ui->radioButton_cut->setChecked(cut_flag);
    ui->pushButton_cancel->setEnabled(false);

    ui->graphicsView->setMouseTracking(true);
    ui->pushButton_hand_mode->setEnabled(true);
    ui->pushButton_cursor_mode->setEnabled(false);
    hand_flag = false;

    data.lines.push_back({});
    data.cut_amount = 0;

    ui->pushButton_hand_mode->setToolTip("Режим масштабирования.");
    ui->pushButton_cursor_mode->setToolTip("Режим ввода точек мышкой.");
    ui->pushButton_reset_scale->setToolTip("Сброс масштабирования.");
}

MainWindow::MainWindow(Test test, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // initial colors;
    data.cut_color = Qt::blue;
    data.line_color = Qt::black;
    data.visible_color = QColor("#FF0000");

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->viewport()->installEventFilter(this);

    ui->radioButton_cut->setChecked(cut_flag);
    ui->pushButton_cancel->setEnabled(false);

    ui->graphicsView->setMouseTracking(true);
    ui->pushButton_hand_mode->setEnabled(true);
    ui->pushButton_cursor_mode->setEnabled(false);
    hand_flag = false;

    data.lines.push_back({});
    data.cut_amount = 0;

    if (!test.isEmpty())
    {
        this->populateTestData(test);
    }
}

void MainWindow::populateTestData(Test test)
{
    if (!test.is_full())
        return;

    putPointNoClick(test.cut().p1, true);
    putPointNoClick(test.cut().p2, true);
    putPointNoClick(test.point_1(), false);
    putPointNoClick(test.point_2(), false);
    on_pushButton_cut_clicked();

    QRectF sceneRect = scene->sceneRect();
    QSize imageSize(sceneRect.size().toSize());
    QImage image(imageSize, QImage::Format_ARGB32);
    image.fill(Qt::white);

    QPainter painter(&image);
    scene->render(&painter);
    QString filename = QString("/Users/administrator/Desktop/qt/C++/lab_07_00/func_data/pics/%1.png").arg(test.name());
    image.save(filename, "png");

    this->deleteLater();
}

void MainWindow::putPointNoClick(point p, bool my_flag)
{
    process_flag = !process_flag;
    point lp = data.lines[data.lines.size() - 1].p1;
    Qt::KeyboardModifiers key = QApplication::queryKeyboardModifiers();
    if (key == Qt::ShiftModifier && !ui->radioButton_cut->isChecked()) {
        point d = { abs(lp.x - p.x), abs(lp.y - p.y) };
        if (d.x < d.y)
            p.x = lp.x;
        else
            p.y = lp.y;
    }
    request req;
    req.operation = ADD_POINT;
    req.data = data;
    req.cut_flag = my_flag;
    req.p = p;
    if (ui->radioButton_cut->isChecked())
        req.number = data.cut_amount + 1;
    req.scene = scene;
    req.view = ui->graphicsView;
    int rc = handle_request(req);
    if (rc == 1)
        error_message("Ошибка при вводе точке! Отсекатель вырожден");
    if (rc == 2)
        error_message("Ошибка при вводе точки! Начальная и конечная точки линии совпадают");
    if (!rc) {
        push_cancel();
        data = req.data;
        data.cut_amount = req.number;
        req.operation = DRAW_ALL;
        handle_request(req);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    cancel = std::stack<content>();
}

void MainWindow::error_message(QString str)
{
    QMessageBox::critical(NULL, "Ошибка", str);
}

void MainWindow::copy(struct content** a, struct content* b)
{
    (*a)->cut = b->cut;
    (*a)->cut_color = b->cut_color;
    (*a)->line_color = b->line_color;
    (*a)->visible_color = b->visible_color;
    (*a)->cut_amount = b->cut_amount;
    for (size_t i = 0; i < b->lines.size(); i++)
        (*a)->lines.push_back(b->lines[i]);
}

void MainWindow::push_cancel()
{
    content* c = new content;
    copy(&c, &data);
    cancel.push(*c);
    ui->pushButton_cancel->setEnabled(true);
}

bool MainWindow::eventFilter(QObject* object, QEvent* event)
{
    if (event->type() == QEvent::MouseMove && object == ui->graphicsView->viewport()) {
        if (!hand_flag) {
            QMouseEvent* my_mouse = static_cast<QMouseEvent*>(event);
            my_mouse_move_event(my_mouse);
            return true;
        }
    }
    if (event->type() == QEvent::Wheel && object == ui->graphicsView->viewport()) {
        if (hand_flag) {
            QWheelEvent* wheel_event = static_cast<QWheelEvent*>(event);
            ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
            double scale_factor = 1.15;
            if (wheel_event->angleDelta().y() > 0)
                ui->graphicsView->scale(scale_factor, scale_factor);
            else
                ui->graphicsView->scale(1 / scale_factor, 1 / scale_factor);
        }
        return true;
    }
    return false;
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    QRect view = ui->graphicsView->geometry();
    if (!hand_flag) {
        if (event->pos().x() >= view.x() && event->pos().x() <= (view.x() + view.width())
            && event->pos().y() >= view.y() && event->pos().y() <= (view.y() + view.height() + menuBar()->geometry().height())) {
            process_flag = !process_flag;
            point p = { event->pos().x() - view.x(), event->pos().y() - view.y() - menuBar()->geometry().height() };
            point lp = data.lines[data.lines.size() - 1].p1;
            Qt::KeyboardModifiers key = QApplication::queryKeyboardModifiers();
            if (key == Qt::ShiftModifier && !ui->radioButton_cut->isChecked()) {
                point d = { abs(lp.x - p.x), abs(lp.y - p.y) };
                if (d.x < d.y)
                    p.x = lp.x;
                else
                    p.y = lp.y;
            }
            add_draw_point(p);
        }
    }
}

void MainWindow::my_mouse_move_event(QMouseEvent* event)
{
    if (!process_flag)
        return;
    QRect view = ui->graphicsView->geometry();
    if (event->pos().x() >= 0 && event->pos().y() >= 0
        && event->pos().x() <= view.width() && event->pos().y() <= view.height()) {
        point p = { event->pos().x(), event->pos().y() };
        point lp = data.lines[data.lines.size() - 1].p1;
        Qt::KeyboardModifiers key = QApplication::queryKeyboardModifiers();
        if (key == Qt::ShiftModifier && !ui->radioButton_cut->isChecked()) {
            point d = { abs(lp.x - p.x), abs(lp.y - p.y) };
            if (d.x < d.y)
                p.x = lp.x;
            else
                p.y = lp.y;
        }
        content* c = new content;
        copy(&c, &data);
        request req;
        req.operation = ADD_POINT;
        req.data = *c;
        req.cut_flag = ui->radioButton_cut->isChecked();
        req.p = p;
        req.number = 2;
        req.scene = scene;
        req.view = ui->graphicsView;
        int rc = handle_request(req);
        if (!rc) {
            req.operation = DRAW_ALL;
            handle_request(req);
        }
        delete c;
    }
}

void MainWindow::add_draw_point(const point& p)
{
    request req;
    req.operation = ADD_POINT;
    req.data = data;
    req.cut_flag = ui->radioButton_cut->isChecked();
    req.p = p;
    if (ui->radioButton_cut->isChecked())
        req.number = data.cut_amount + 1;
    req.scene = scene;
    req.view = ui->graphicsView;
    int rc = handle_request(req);
    if (rc == 1)
        error_message("Ошибка при вводе точке! Отсекатель вырожден");
    if (rc == 2)
        error_message("Ошибка при вводе точки! Начальная и конечная точки линии совпадают");
    if (!rc) {
        push_cancel();
        data = req.data;
        data.cut_amount = req.number;
        req.operation = DRAW_ALL;
        handle_request(req);
    }
}
