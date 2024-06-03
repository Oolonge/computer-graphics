#include <QApplication>
#include <QDebug>
#include <QDir>

#include "mainwindow.h"
#include "testparser.h"

void createNewWindow(MainWindow *w, const QList<Test> &tests, qsizetype &cur) {
    if (cur < tests.size())
    {
        if (cur == 0)
            qDebug() << "***** НАЧАЛО ФУНКЦИОНАЛЬНОГО ТЕСТИРОВАНИЯ *****";

        Test test = tests[cur++];
        qDebug() << test;
        w = new MainWindow(test);
        QObject::connect(w, &MainWindow::destroyed,
                         [&]() { createNewWindow(w, tests, cur); });
    }
    else
    {
        qDebug() << "***** КОНЕЦ ФУНКЦИОНАЛЬНОГО ТЕСТИРОВАНИЯ *****";
        qDebug() << "Тестов пройдено:" << tests.count()
                 << "| результаты находятся в папке ./func/pics/";
        QCoreApplication::quit();
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TestParser parser;
    QList<Test> tests;
    MainWindow *w = nullptr;
    qsizetype cur = 0;

    QString appPath = "/Users/administrator/Desktop/qt/C++/lab_10_00/func_data/tests.json";
    parser.loadFromFile(appPath);
    tests = parser.tests();

    createNewWindow(w, tests, cur);

    return a.exec();
}
