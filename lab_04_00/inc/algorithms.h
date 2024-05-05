#ifndef algorithmS_H
#define algorithmS_H

#include "structures.h"

int sign(double x); //artificial func to use in unit_tests, since all the others return void.

void circleStandard(canvas_t &scene, const figure_t &circle);
void circleCanonical(canvas_t &scene, const figure_t &circle, const bool &drawingFlag);
void circleParametrical(canvas_t &scene, const figure_t &circle, const bool &drawingFlag);
void circleBresen(canvas_t &scene, const figure_t &circle, const bool &drawingFlag);
void circleMiddlePoint(canvas_t &scene, const figure_t &circle, const bool &drawingFlag);

void ellipseStandard(canvas_t &scene, const figure_t &ellipse);
void ellipseCanonical(canvas_t &scene, const figure_t &ellipse, const bool &drawingFlag);
void ellipseParametrical(canvas_t &scene, const figure_t &ellipse, const bool &drawingFlag);
void ellipseBresen(canvas_t &scene, const figure_t &ellipse, const bool &drawingFlag);
void ellipseMiddlePoint(canvas_t &scene, const figure_t &ellipse, const bool &drawingFlag);

#endif // algorithmS_H
