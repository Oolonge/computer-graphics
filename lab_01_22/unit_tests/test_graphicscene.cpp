#include "../unit_tests/test_graphicscene.h"
#include "../inc/graphicscene.h"

TestGraphicScene::TestGraphicScene(QObject *parent) : QObject(parent) {}

void TestGraphicScene::isDegenerate() {
  GraphicScene a(0.0, 0.0, 100.0, 100.0, false);
  QCOMPARE(a.isDegenerate(qreal(1), qreal(3), qreal(1)), true);
}

// QTEST_MAIN(TestGraphicScene)
