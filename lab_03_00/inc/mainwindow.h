#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPushButton>
#include <QLabel>
#include <stack>
#include <fstream>
#include <QColorDialog>
#include <QColor>
#include <QMessageBox>
#include <QWheelEvent>
#include <iostream>
#include <QTimer>
#include <QDrag>
#include <QMimeData>
#include <QtGlobal>
#include <cmath>

#include "algorithms.h"
#include "consts.h"
#include "ui_mainwindow.h"

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int drawLine(line_t &line, bool is_drawing, bool is_cnt_steps);
    void drawSpectrum(spectre_t &spectrum);

    double MeasureAverageTime(spectre_t spectrum);
    void MeasureSteps(spectre_t spectrum, std::vector<int> &steps);

public slots:
    //overrides
    virtual bool eventFilter(QObject *object, QEvent *event) override;
    virtual void showEvent(QShowEvent *ev) override;
    virtual void wheelEvent(QWheelEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;

    //display
    void outputError(QString str);
    void outputSuccess(QString str);
    void displayColor(QColor color, QLabel *button);

    //drawing
    void drawAxes();
    void drawAll();

    //measurements
    void steps_count();
    void time_measure();

private slots:
    //button events
    void on_pushButtonBackgroundColor_clicked();
    void on_pushButtonLineColor_clicked();
    void on_pushButtonDrawLine_clicked();
    void on_pushButtonDrawSpectrum_clicked();
    void on_pushButtonClear_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonResetScale_clicked();

    //menu events
    void on_program_info_action_triggered();
    void on_author_info_action_triggered();
    void on_exit_action_triggered();
    void on_time_action_triggered();
    void on_steps_action_triggered();

private:

    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    QColor line_color = Qt::black;
    QColor backgroundColor = Qt::white;

    objects_t data;
    QPointF max, min;
    std::stack<objects_t> cancel_stack;


    void setBackroundColor();
    void setLineColor();
    void readLineData();
    void readSpectrumData();
    void clearCanvas();
    void cancelAction();
};
#endif // MAINWINDOW_H
