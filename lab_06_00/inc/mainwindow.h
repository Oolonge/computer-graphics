#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QLabel>
#include <stack>
#include <QTableWidgetItem>
#include "structures.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //overrides
    bool eventFilter(QObject *object, QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

    //additional funcs
    void error_message(QString str);
    void copy(struct content **a, struct content *b);

private slots:
    // implemented in color.cpp
    void show_color(QColor color, QLabel *lab);
    void color_dialog(QColor &color);
    void on_pushButton_line_color_clicked();
    void on_pushButton_fill_color_clicked();

    // implemented in table_widget.cpp
    void on_pushButton_del_point_clicked();
    void on_tableWidget_cellClicked(int row);
    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    // implemented in buttons.cpp
    void on_comboBox_activated(int index);
    void on_pushButton_close_clicked();
    void on_pushButton_add_hole_clicked();
    void on_pushButton_clear_clicked();
    void on_pushButton_reset_scale_clicked();
    void on_pushButton_cancel_clicked();
    void on_pushButton_fill_clicked();
    void on_pushButton_hand_mode_clicked();
    void on_pushButton_cursor_mode_clicked();
    void on_pushButton_seed_point_click_clicked();
    void on_pushButton_seed_point_key_clicked();

    // menu events (menu.cpp)
    void on_program_info_action_triggered();
    void on_author_info_action_triggered();
    void on_exit_action_triggered();

private:
    Ui::MainWindow *ui;
    canvas_t scene;
    QColor fill_color = QColor("#0ABAB5");
    QColor back_color = Qt::white;
    QColor line_color = Qt::black;
    content data;
    std::stack<content> cancel;
    int count = 0;
    bool hole_flag = false;
    bool hand_flag = false;
    bool seed_point_flag = false;
};
#endif // MAINWINDOW_H
