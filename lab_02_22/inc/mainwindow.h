#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "errors.h"
#include "task_performer.h"
#include "../func_data/test.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    explicit MainWindow(Test test, QWidget *parent = nullptr);
    ~MainWindow();

    void populateTestData(Test test);
private slots:
    void on_button_Move_clicked();
    void on_button_Scale_clicked();
    void on_button_Turn_clicked();
    void on_actionOpen_triggered();
    void on_button_Turn_released();

private:
    Ui::MainWindow *ui;
};

errors draw_action(Ui::MainWindow* ui);
errors transform_and_show(request req, Ui::MainWindow* ui);

#endif // MAINWINDOW_H
