#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "consts.h"
#include "mainwindow.h"

void standart_line(line_t &line, graphics_t scene);
int dda_line(line_t &line, graphics_t scene, bool drawingFlag, bool countStepsFlag);
int bresen_double_line(line_t &line, graphics_t scene, bool drawingFlag, bool countStepsFlag);
int bresen_int_line(line_t &line, graphics_t scene, bool drawingFlag, bool countStepsFlag);
int bresen_steps_line(line_t &line, graphics_t scene, bool drawingFlag, bool countStepsFlag);
int wy_line(line_t &line, graphics_t scene, bool drawingFlag, bool countStepsFlag);

#endif // ALGORITHMS_H
