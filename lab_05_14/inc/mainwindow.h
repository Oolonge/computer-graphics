#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QLabel>
#include <stack>
#include <QTableWidgetItem>
#include "structures.h"
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

    // overrides
    virtual bool eventFilter(QObject *object, QEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;

    // additional funcs
    void error_message(QString str);
    void copy(struct content** a, struct content* b);

    //func testing
    void populateTestData(Test test);
    void addPointNoClick(point p);
private slots:
    // implemented in color.cpp
    void on_pushButton_line_color_clicked();
    void show_color(QColor color, QLabel *lab);
    void color_dialog(QColor &color);
    void on_pushButton_fill_color_clicked();

    // implemented in table_widget.cpp
    void on_tableWidget_cellClicked(int row);
    void on_pushButton_del_point_clicked();

    // implemented in buttons.cpp
    void on_comboBox_activated(int index);
    void on_pushButton_close_clicked();
    void on_pushButton_add_hole_clicked();
    void on_pushButton_clear_clicked();
    void on_pushButton_cancel_clicked();
    void on_pushButton_fill_clicked();
    void on_pushButton_reset_scale_clicked();
    void on_pushButton_drag_mode_clicked();
    void on_pushButton_cursor_mode_clicked();

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
};
#endif // MAINWINDOW_H
