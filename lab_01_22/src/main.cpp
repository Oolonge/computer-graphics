#include "../inc/mainwindow.h"

#include "../inc/graphicscene.h"
#include "../unit_tests/test_graphicscene.h"
#include <QApplication>
#include <QTest>
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  // QTest::qExec(new TestGraphicScene, argc, argv);
  return a.exec();
}
