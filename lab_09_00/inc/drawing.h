#ifndef DRAWING_H
#define DRAWING_H

#include "structures.h"

void drawLine(const line& line, QPainter& paint);
void drawPolygon(const polygon& cut, QPainter& paint);
void drawAll(const content& data, canvas_t& scene, gv_t& view);

#endif // DRAWING_H
