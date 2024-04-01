#ifndef TASK_PERFORMER_H
#define TASK_PERFORMER_H

#include "drawing.h"
#include "operations.h"

enum task
{
    INIT,
    LOAD_FILE,
    DRAW,
    MOVE,
    SCALE,
    TURN,
    QUIT
};

struct load_file
{
    const char* filename;
};

struct request
{
    task t;
    union
    {
        struct load_file load_f;
        struct draw dr;
        struct move mo;
        struct scale sc;
        struct turn tu;
    };
};

int task_performer(request args);

#endif // TASK_PERFORMER_H
