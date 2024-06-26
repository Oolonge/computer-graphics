#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "task_performer.h"
#include "errors.h"
#include "operations.h"
#include "projection.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    request req;
    req.t = INIT;
    task_performer(req);
}

MainWindow::MainWindow(Test test, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    request req;
    req.t = INIT;
    task_performer(req);

    if (!test.isEmpty()) {
        this->populateTestData(test);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::populateTestData(Test test)
{
    on_actionOpen_triggered();

    request req;
    if (test.is_scale_)
    {
        req.t = SCALE;
        req.sc = test.get_scale();

        errors err = transform_and_show(req, ui);
        if (err)
            error_message(err);
    }

    if (test.is_turn_)
    {
        req.t = TURN;
        req.tu = test.get_turn();

        errors err = transform_and_show(req, ui);
        if (err)
            error_message(err);
    }

    if (test.is_move_)
    {
        req.t = MOVE;
        req.mo = test.get_move();

        errors err = transform_and_show(req, ui);
        if (err)
            error_message(err);
    }

    // draw dr;

    // dr.gV = ui->graphicsView;
    // dr.h = ui->graphicsView->height();
    // dr.w = ui->graphicsView->width();

    // graphics a;
    // a.scene = new QGraphicsScene(dr.gV);
    // if (!a.scene)
    //     return PTR_ALLOC_ERR;
    // a.pen = QPen(Qt::black);

    // draw_connections(fig.points, fig.connections, dr, a);

    // a.scene->setSceneRect(QRectF(QPointF(0, 0), QSizeF(dr.w, dr.h)));
    // set_scene(dr.gV, a);

    // QImage image((ui->graphicsView->rect()).size(), QImage::Format_ARGB32);
    // image.fill(Qt::transparent);

    // errors err = transform_and_show(req, ui);
    // if (err)
    //     error_message(err);

    // QPainter painter(&image);
    // scene->render(&painter);

    // draw_action(ui, &image);

    // image.mirror();
    // QString filename = QCoreApplication::applicationDirPath() + "/" + QString("../func/%1.png").arg(test.name());
    // image.save(filename, "png");

    this->deleteLater();
}

errors draw_action(Ui::MainWindow* ui)
{
    draw dr;

    dr.gV = ui->graphicsView;
    dr.h = ui->graphicsView->height();
    dr.w = ui->graphicsView->width();

    request req;
    req.t = DRAW;
    req.dr = dr;

    errors err = (errors) task_performer(req);
    return err;
}

errors transform_and_show(request req, Ui::MainWindow* ui)
{
    errors err = (errors) task_performer(req);
    if (err)
        return err;
    else
        err = draw_action(ui);

    return err;
}

// Load figure
void MainWindow::on_actionOpen_triggered()
{
    request req;
    req.t = LOAD_FILE;

    req.load_f.filename = "/Users/administrator/Desktop/qt/C++/lab_02_22/cube.txt";

    errors err = transform_and_show(req, ui);
    if (err)
        error_message(err);
}

// Transformation
void MainWindow::on_button_Move_clicked()
{
    request req;
    req.t = MOVE;

    req.mo.dx = ui->lineEdit_MoveX->text().toInt();
    req.mo.dy = ui->lineEdit_MoveY->text().toInt();

    errors err = transform_and_show(req, ui);
    if (err)
        error_message(err);
}

void MainWindow::on_button_Scale_clicked()
{
    request req;
    req.t = SCALE;

    req.sc.kx = ui->lineEdit_ScaleX->text().toFloat();
    req.sc.ky = ui->lineEdit_ScaleY->text().toFloat();

    errors err = transform_and_show(req, ui);
    if (err)
        error_message(err);
}

void MainWindow::on_button_Turn_clicked()
{
    request req;
    req.t = TURN;

    req.tu.ox = ui->lineEdit_TurnX->text().toFloat();
    req.tu.oy = ui->lineEdit_TurnY->text().toFloat();

    errors err = transform_and_show(req, ui);
    if (err)
        error_message(err);
}

void MainWindow::on_button_Turn_released()
{

}
