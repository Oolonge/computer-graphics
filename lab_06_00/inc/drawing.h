#ifndef DRAWING_H
#define DRAWING_H

#include "structures.h"

void drawPoints(canvas_t &scene, gv_t &gv, const bool &is_sel, const point &selected_p, const content &data);
void drawConnection(const point &p1, const point &p2, QPainter &p);
void drawPoint(canvas_t &scene, gv_t &gv, const point &selected_p, const content &data);

#endif // DRAWING_H
