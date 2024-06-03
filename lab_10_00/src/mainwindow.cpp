#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsView>
#include <QMessageBox>
#include <QTime>
#include <QLineF>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
    background_color(Qt::black), color(Qt::white)
{
    ui->setupUi(this);

    functions = {functions::func1, functions::func2, functions::func3, functions::func4};

    setup_scene();
    setup_buttons();
}

MainWindow::MainWindow(Test test, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
    background_color(Qt::black), color(Qt::white)
{
    ui->setupUi(this);

    functions = {functions::func1, functions::func2, functions::func3, functions::func4};

    setup_scene();

    if (!test.isEmpty())
    {
        this->populateTestData(test);
    }
}

void MainWindow::populateTestData(Test test)
{
    if (!test.is_full())
        return;

    QList<double> x_border = test.x_border();
    QList<double> z_border = test.z_border();
    QList<double> rotation = test.transformations();

    auto func = functions[test.function_index()];
    double scale = test.scale_coefficient();

    auto interval_x = horizon::Interval(x_border[0], x_border[1], x_border[2]);
    auto interval_z = horizon::Interval(z_border[0], z_border[1], z_border[2]);
    auto rotation_res = horizon::Rotation(rotation[0], rotation[1], rotation[2]);
    auto transformation = horizon::Transformation(rotation_res, scale);

    auto lines = horizon::horizon_method(ui->graphicsView,
                                         interval_x,
                                         interval_z,
                                         func,
                                         transformation);

    draw_lines(lines);

    QRectF sceneRect = scene->sceneRect();
    QSize imageSize(sceneRect.size().toSize());
    QImage image(imageSize, QImage::Format_ARGB32);
    image.fill(Qt::black);

    QPainter painter(&image);
    scene->render(&painter);
    QString filename = QString("/Users/administrator/Desktop/qt/C++/lab_10_00/func_data/pics/%1.png").arg(test.name());
    image.save(filename, "png");

    this->deleteLater();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}

void MainWindow::setup_scene()
{
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setBackgroundBrush(background_color);
}

void MainWindow::setup_buttons()
{
    connect(ui->plotBtn, &QPushButton::clicked, this, &MainWindow::plot);
    connect(ui->clearBtn, &QPushButton::clicked, this, &MainWindow::clear);
}

void MainWindow::plot()
{
    auto [x_interval, z_interval, transform] = get_data();
    if (!x_interval || !z_interval || !transform) {
        return;
    }

    scene->clear();
    auto func = functions[ui->comboBox->currentIndex()];

    QElapsedTimer timer;
    timer.start();

    auto lines = horizon::horizon_method(ui->graphicsView, *x_interval, *z_interval, func, *transform);
    draw_lines(lines);

    update_time_label(timer.elapsed() / 1000.0);
}

void MainWindow::draw_line(const QLineF& line, const QColor& color)
{
    QPen pen(color);
    scene->addLine(line, pen);
}

void MainWindow::draw_lines(const std::vector<QLineF>& lines)
{
    for (const auto& line : lines) {
        draw_line(line, color);
    }
}

void MainWindow::update_time_label(double time)
{
    ui->timeLabel->setText(QString::number(time * 1000, 'f', 4) + " мс");
}

std::tuple<std::optional<horizon::Interval>, std::optional<horizon::Interval>, std::optional<horizon::Transformation>> MainWindow::get_data()
{
    return {get_x_interval(), get_z_interval(), get_transformation()};
}

std::optional<horizon::Interval> MainWindow::get_x_interval()
{
    try {
        double start_x = ui->x_start->toPlainText().toDouble();
        double end_x = ui->x_end->toPlainText().toDouble();
        double step_x = ui->x_step->toPlainText().toDouble();
        return horizon::Interval(start_x, end_x, step_x);
    } catch (...) {
        QMessageBox::warning(this, "Ошибка", "Некорректные данные в полях ввода интервала по оси X");
        return std::nullopt;
    }
}

std::optional<horizon::Interval> MainWindow::get_z_interval()
{
    try {
        double start_z = ui->z_start->toPlainText().toDouble();
        double end_z = ui->z_end->toPlainText().toDouble();
        double step_z = ui->z_step->toPlainText().toDouble();
        return horizon::Interval(start_z, end_z, step_z);
    } catch (...) {
        QMessageBox::warning(this, "Ошибка", "Некорректные данные в полях ввода интервала по оси Z");
        return std::nullopt;
    }
}

std::optional<horizon::Transformation> MainWindow::get_transformation()
{
    auto rotation = get_angles();
    auto scale_ratio = get_scale_ratio();
    if (rotation && scale_ratio) {
        return horizon::Transformation(*rotation, *scale_ratio);
    }
    return std::nullopt;
}

std::optional<horizon::Rotation> MainWindow::get_angles()
{
    try {
        double angle_x = ui->angle_x->toPlainText().toDouble();
        double angle_y = ui->angle_y->toPlainText().toDouble();
        double angle_z = ui->angle_z->toPlainText().toDouble();
        return horizon::Rotation(angle_x, angle_y, angle_z);
    } catch (...) {
        QMessageBox::warning(this, "Ошибка", "Некорректные данные в полях ввода углов поворота");
        return std::nullopt;
    }
}

std::optional<double> MainWindow::get_scale_ratio()
{
    try {
        double scale = ui->scale->toPlainText().toDouble();
        if (scale < 1e-7) {
            throw std::invalid_argument("Scale too small");
        }
        return scale;
    } catch (...) {
        QMessageBox::warning(this, "Ошибка", "Некорректные данные в поле ввода коэффициента масштабиро-вания");
        return std::nullopt;
    }
}

void MainWindow::clear()
{
    scene->clear();
}
