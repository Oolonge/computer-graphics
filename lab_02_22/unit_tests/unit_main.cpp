#include "unit_tests.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  int status = 0;
  status |= QTest::qExec(new TestTaskPerformer, argc, argv);
  return status;
}

