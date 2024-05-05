#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include "structures.h"

enum operation_t
{
    DRAW_CIRCLE,
    DRAW_ELLIPSE,
    DRAW_CIRCLE_SPECTRUM,
    DRAW_ELLIPSE_SPECTRUM,
    DRAW_ALL
};

struct request
{
    canvas_t scene;
    gv_t gv;
    operation_t operation;
    figure_t figure;
    spectrum_t spectrum;
    content_t data;
};

void handle_request(request &req);

#endif // REQUEST_HANDLER_H
