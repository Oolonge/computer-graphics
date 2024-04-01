#ifndef PROJECTION_H
#define PROJECTION_H
#include "volumetric_point.h"
#include "io.h"
#include "drawing.h"
#include "operations.h"

#define ASTR_PTS_AMOUNT 100

struct projection
{
    points_data points;
    connections_data connections;
};

projection& init();
void empty_figure(projection& fig);
void copy_figure(projection& fig, projection& tmp);
int fill_figure_fields(projection& fig, FILE *f);
int load_figure_from_file(projection &ob, const char *filename);

int draw_figure(projection fig, draw arg);

int move_figure(projection& fig, move coeff);
int scale_figure(projection& fig, scale coeff);
int turn_figure(projection& fig, turn coeff);

#endif // PROJECTION_H
