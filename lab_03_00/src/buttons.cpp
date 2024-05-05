#include "mainwindow.h"

void MainWindow::on_pushButtonBackgroundColor_clicked()
{
    setBackroundColor();
}

void MainWindow::on_pushButtonLineColor_clicked()
{
    setLineColor();
}

void MainWindow::on_pushButtonDrawLine_clicked()
{
    readLineData();
}

void MainWindow::on_pushButtonDrawSpectrum_clicked()
{
    readSpectrumData();
}

void MainWindow::on_pushButtonClear_clicked()
{
    clearCanvas();
}

void MainWindow::on_pushButtonCancel_clicked()
{
    cancelAction();
}

void MainWindow::on_pushButtonResetScale_clicked()
{
    ui->graphicsView->resetTransform();
}
