#ifndef REQUESTS_H
#define REQUESTS_H

#include "structures.h"

enum type_operation {
    ADD_POINT,
    CUT,
    DRAW_ALL
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

void cutDraw(content& data, canvas_t& scene, gv_t& view);
int request_handle(request& req);

#endif // REQUESTS_H
