#include "mainwindow.h"

void MainWindow::on_program_info_action_triggered()
{
    QMessageBox::information(NULL, "О программе","Реализация и исследование алгоритмов построения отрезков");
}


void MainWindow::on_author_info_action_triggered()
{
    QMessageBox::information(NULL, "Об авторе", " Программа написана студентом ИУ7-41Б\nОвчинниковым Ярославом\ntelegram: @oolonge");
}


void MainWindow::on_exit_action_triggered()
{
    QMessageBox quit_msg;
    quit_msg.setText("Работа с программой будет завершена");
    quit_msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    quit_msg.setIcon(QMessageBox::Warning);
    quit_msg.setDefaultButton(QMessageBox::Ok);
    int rc = quit_msg.exec();
    if (rc == QMessageBox::Ok)
        qApp->quit();
}

void MainWindow::on_time_action_triggered()
{
    steps_count();
}


void MainWindow::on_steps_action_triggered()
{
    time_measure();
}
