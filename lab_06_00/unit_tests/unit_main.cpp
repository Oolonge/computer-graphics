#include "unit_fill.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    int status = 0;
    status |= QTest::qExec(new TestFill, argc, argv);
    return status;
}
