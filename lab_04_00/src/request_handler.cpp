#include "request_handler.h"
#include "drawing.h"
#include <fstream>
#include <ctime>

void handle_request(request &req)
{
    switch (req.operation)
    {
        case DRAW_CIRCLE:
            drawCircle(req.scene, req.figure, true);
            break;
        case DRAW_ELLIPSE:
            drawEllipse(req.scene, req.figure, true);
            break;
        case DRAW_CIRCLE_SPECTRUM:
            drawCircleSpectrum(req.scene, req.spectrum);
            break;
        case DRAW_ELLIPSE_SPECTRUM:
            drawElipseSpectrum(req.scene, req.spectrum);
            break;
        case DRAW_ALL:
            drawAll(req.scene, req.gv, req.data);
            break;
    }
}
