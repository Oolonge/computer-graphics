#ifndef REQUESTS_H
#define REQUESTS_H

#include "structures.h"

enum operation_type {
    ADD_POINT,
    DRAW_ALL,
    CUT
};

struct request {
    operation_type operation;
    content data;
    canvas_t scene;
    gv_t view;
    point p;
    bool cut_flag;
    int number;
};

void cutDraw(content& data, canvas_t& scene, gv_t& view);
int handle_request(request& req);

#endif // REQUESTS_H
