#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QLabel>
#include <QWheelEvent>
#include <stack>
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

public slots:
    //overrides
    virtual bool eventFilter(QObject *object, QEvent *event) override;
    virtual void showEvent(QShowEvent *ev) override;
    virtual void wheelEvent(QWheelEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;

    //additional funcs
    void displayColor(QColor color, QLabel *lab);
    void errorMessage(QString str);
    void drawAll();

private slots:
    //figure choice
    void on_comboBox_figure_activated(int index);

    //button events
    void on_pushButton_back_color_clicked();
    void on_pushButton_line_color_clicked();
    void on_pushButton_figure_clicked();
    void on_pushButton_spectrum_clicked();
    void on_pushButton_reset_scale_clicked();
    void on_pushButton_cancel_clicked();
    void on_pushButton_clear_clicked();

    //menu events
    void on_program_info_action_triggered();
    void on_author_info_action_triggered();
    void on_exit_action_triggered();

private:
    Ui::MainWindow *ui;
    std::stack<content_t> cancel;
    canvas_t scene;
    content_t data;
    QColor line_color = Qt::black;
    QColor back_color = Qt::white;
};
#endif // MAINWINDOW_H
