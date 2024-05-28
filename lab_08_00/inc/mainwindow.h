#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "structures.h"
#include <QColor>
#include <QLabel>
#include <QMainWindow>
#include <stack>
#include "../func_data/test.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    explicit MainWindow(Test test, QWidget *parent = nullptr);
    ~MainWindow();

    // overrides
    bool eventFilter(QObject* object, QEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

    // additional funcs
    void my_mouse_move_event(QMouseEvent* event);
    void copy(struct content** a, struct content* b);
    void push_cancel();
    void error_message(QString str);
    void add_draw_point(const point& p);
    void find_parallel_point(point &p);

    // for functional tests
    void populateTestData(Test test);
    void addPointNoClick(point p, bool my_cut_flag);

private slots:
    // implemented in color.cpp
    void show_color(QColor color, QLabel* lab);
    void color_dialog(QColor& color);
    void on_pushButton_line_color_clicked();
    void on_pushButton_cut_color_clicked();
    void on_pushButton_visible_line_color_clicked();

    // implemented in buttons.cpp
    void on_pushButton_cancel_clicked();
    void on_pushButton_add_point_clicked();
    void on_pushButton_clear_clicked();
    void on_pushButton_cut_clicked();
    void on_pushButton_reset_scale_clicked();
    void on_pushButton_cursor_mode_clicked();
    void on_pushButton_hand_mode_clicked();
    void on_pushButton_close_cut_clicked();

    // menu events (menu.cpp)
    void on_program_info_action_triggered();
    void on_author_info_action_triggered();
    void on_exit_action_triggered();

private:
    Ui::MainWindow* ui;
    QGraphicsScene* scene;
    content data;
    std::stack<content> cancel;
    bool cut_flag = true;
    bool process_flag = false;
    bool hand_flag = false;
};
#endif // MAINWINDOW_H
