#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    taskptr = new TaskPopup;
    solutionptr = new solutionpopup;
    aboutptr = new aboutpopup;
    ui->setupUi(this);
    connect(ui->showTaskButton, SIGNAL(clicked(bool)), this, SLOT(showTask()));
    connect(ui->showSolutionButton, SIGNAL(clicked(bool)), this, SLOT(showSolution()));
    connect(ui->showAboutButton, SIGNAL(clicked(bool)), this, SLOT(showAbout()));
}

MainWindow::~MainWindow()
{
    delete taskptr;
    delete solutionptr;
    delete aboutptr;
    delete ui;
}

void MainWindow::showTask()
{
    taskptr->show();
}

void MainWindow::showSolution()
{
    solutionptr->show();
}

void MainWindow::showAbout()
{
    aboutptr->show();
}

void MainWindow::on_quitButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Выход", "Выйти?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
        QApplication::quit();
    } else {
        qDebug() << "Yes was *not* clicked";
    }
}

