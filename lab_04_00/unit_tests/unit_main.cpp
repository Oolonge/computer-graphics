#include "../unit_tests/test_algorithms.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    int status = 0;
    status |= QTest::qExec(new TestAlgorithms, argc, argv);
    return status;
}

