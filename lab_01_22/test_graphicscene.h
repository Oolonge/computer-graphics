#ifndef TEST_GRAPHICSCENE_H
#define TEST_GRAPHICSCENE_H

#include <QTest>
#include "graphicscene.h"

class TestGraphicScene : public QObject
{
    Q_OBJECT
public:
    explicit TestGraphicScene(QObject *parent = 0);

private slots:
    void initTestCase()
    { qDebug("called before everything else"); }
    void isDegenerate(); //bool isDegenerate(qreal, qreal, qreal)
    void cleanupTestCase()
    { qDebug("called after the first test"); }
};


#endif // TEST_GRAPHICSCENE_H
