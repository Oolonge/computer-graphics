#include "mainwindow.h"
#include "unit_tests.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QTest::qExec(new TestTaskPerformer, argc, argv);

    return a.exec();
}
