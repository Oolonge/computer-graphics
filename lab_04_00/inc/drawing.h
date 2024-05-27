#ifndef DRAWING_H
#define DRAWING_H

#include "structures.h"

void drawAll(canvas_t &scene, gv_t &gv, const content_t &data);
void drawCircle(canvas_t &scene, const figure_t &data, const bool &drawingFlag);
void drawEllipse(canvas_t &scene, const figure_t &data, const bool &drawingFlag);
void drawCircleSpectrum(canvas_t &scene, const spectrum_t &spectrum);
void drawElipseSpectrum(canvas_t &scene, const spectrum_t &spectrum);
void drawCircleReflect(canvas_t &scene, const QPointF &point, const QPointF &center, const QColor &color);
void drawEllipseReflect(canvas_t &scene, const QPointF &point, const QPointF &center, const QColor &color);
void drawing_axes(canvas_t &scene);

#endif // DRAWING_H
