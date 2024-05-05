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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    ui->pushButton_cancel->setEnabled(false);

    ui->lineEdit_figure_r2->setDisabled(true);
    ui->lineEdit_spectrum_dr2->setDisabled(true);
    ui->lineEdit_spectrum_r2->setDisabled(true);

    data.back_color = Qt::white;
    displayColor(data.back_color, ui->label_bc);
    displayColor(line_color, ui->label_lc);

    ui->graphicsView->viewport()->installEventFilter(this);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    cancel = std::stack <content_t>();
}

//overrides
void MainWindow::showEvent(QShowEvent *ev)
{
    QMainWindow::showEvent(ev);
    QTimer::singleShot(700, this, SLOT(drawAll()));
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    ui->graphicsView->resetTransform();
    drawAll();
}

void MainWindow::wheelEvent(QWheelEvent* event)
{
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    double scale_coeff = 1.05;
    if (event->angleDelta().y() > 0)
        ui->graphicsView->scale(scale_coeff, scale_coeff);
    else
        ui->graphicsView->scale(1 / scale_coeff, 1 / scale_coeff);
}

bool MainWindow::eventFilter(QObject* object, QEvent* event)
{
    if (event->type() == QEvent::Wheel && object == ui->graphicsView->viewport())
    {
        QWheelEvent *wheel_event = static_cast<QWheelEvent *>(event);
        wheelEvent(wheel_event);
        return true;
    }
    return false;
}


void MainWindow::errorMessage(QString str)
{
    QMessageBox::critical(NULL, "Ошибка", str);
}

void MainWindow::drawAll()
{
    request req;
    req.operation = DRAW_ALL;
    req.data = data;
    req.scene = scene;
    req.gv = ui->graphicsView;
    handle_request(req);
}

// displaying color on label
void MainWindow::displayColor(QColor color, QLabel *lab)
{
    QImage im = QImage(lab->geometry().width(), lab->geometry().height(), QImage::Format_RGB32);
    QPainter p(&im);
    p.setBrush(QBrush(color));
    p.setPen(Qt::black);
    QRect rect = QRect(0, 0, lab->geometry().width(), lab->geometry().height());
    p.drawRect(rect);

    QPixmap pixmap = QPixmap::fromImage(im);
    lab->clear();
    lab->setPixmap(pixmap);
}
