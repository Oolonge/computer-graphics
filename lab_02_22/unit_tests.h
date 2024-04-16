#ifndef UNIT_TESTS_H
#define UNIT_TESTS_H

#include <QTest>

#include "task_performer.h"
#include "errors.h"

class TestTaskPerformer : public QObject
{
    Q_OBJECT
public:
    explicit TestTaskPerformer(QObject *parent = 0);

private slots:
    void initTestCase()
    { qDebug("called before everything else"); }

    // int task_performer(request req)
    void taskLoadFile();

    void cleanupTestCase()
    { qDebug("called after the first test"); }
};


#endif // UNIT_TESTS_H
