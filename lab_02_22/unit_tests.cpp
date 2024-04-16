#include "unit_tests.h"

TestTaskPerformer::TestTaskPerformer(QObject *parent) :
    QObject(parent)
{
}

void TestTaskPerformer::taskLoadFile()
{
    request req = { LOAD_FILE, {"non_existant_file.txt"} };
    QCOMPARE(task_performer(req), FILE_NOT_FOUND);
}
