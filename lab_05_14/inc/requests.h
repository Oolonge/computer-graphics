#ifndef REQUESTS_H
#define REQUESTS_H

#include "structures.h"
#include <QTableWidget>

enum operation
{
    DRAW,
    FILL_AREA,
    ADD_POINT,
    DELETE_POINT,
    SELECT_POINT,
    CANCEL_ACTION,
    CHANGE_POINT
};

struct request
{
    operation oper;
    content data;
    canvas_t scene;
    gv_t view;
    QTableWidget *table;
    point p;
    colors colors_data;
    indexes indexes_data;
    std::vector<double> time;
    int delay;
    bool hole_figure_flag;
};

int handle_request(request &req);

#endif // REQUESTS_H
