#ifndef DRAWING_H
#define DRAWING_H

#include "structures.h"

void DrawAll(const content& data, canvas_t& scene, gv_t& view);
void drawLine(const line& line, QPainter& paint);

#endif // DRAWING_H
