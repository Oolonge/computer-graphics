#ifndef DRAWING_H
#define DRAWING_H

#include "structures.h"

void DrawAll(const content& data, canvas_t& scene, gv_t& view);
void drawCutLine(const figure& line, QPainter& paint);

#endif // DRAWING_H
