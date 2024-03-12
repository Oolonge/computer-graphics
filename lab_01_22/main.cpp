#include "mainwindow.h"

#include <QApplication>
#include <QTest>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "test_graphicscene.h"
#include "graphicscene.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QTest::qExec(new TestGraphicScene, argc, argv);

    return a.exec();
}
