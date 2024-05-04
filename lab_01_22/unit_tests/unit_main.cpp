#include "test_graphicscene.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  int status = 0;
  status |= QTest::qExec(new TestGraphicScene, argc, argv);
  return status;
}
