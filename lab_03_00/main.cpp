#include "mainwindow.h"
#include "test_algorithms.h"

#include <QApplication>
#include <QTest>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QTest::qExec(new TestAlgorithms, argc, argv);

    return a.exec();
}
