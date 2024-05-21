#ifndef REQUESTS_H
#define REQUESTS_H

#include "structures.h"

enum type_operation {
    ADD_POINT,
    DRAW_ALL,
    CUT
};

struct request {
    type_operation operation;
    content data;
    bool cut_flag;
    canvas_t scene;
    gv_t view;
    point p;
    int number;
};

int request_handle(request& req);

#endif // REQUESTS_H
