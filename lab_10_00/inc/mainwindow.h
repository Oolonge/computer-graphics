#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QGraphicsScene>
#include <optional>
#include "horizon.h"
#include "functions.h"
#include "../func_data/test.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    explicit MainWindow(Test test, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void plot();
    void clear();

private:
    void setup_scene();
    void setup_buttons();
    // void setup_input_fields();

    void draw_line(const QLineF& line, const QColor& color);
    void draw_lines(const std::vector<QLineF>& lines);

    void update_time_label(double time);

    std::tuple<std::optional<horizon::Interval>, std::optional<horizon::Interval>, std::optional<horizon::Transformation>> get_data();
    std::optional<horizon::Interval> get_x_interval();
    std::optional<horizon::Interval> get_z_interval();
    std::optional<horizon::Transformation> get_transformation();
    std::optional<horizon::Rotation> get_angles();
    std::optional<double> get_scale_ratio();

    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QColor background_color;
    QColor color;

    std::vector<std::function<double(double, double)>> functions;

    void populateTestData(Test test);
};

#endif // MAINWINDOW_H
