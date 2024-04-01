#ifndef DRAWING_H
#define DRAWING_H
#include "QGraphicsView"
#include "graphics.h"
#include "volumetric_point.h"
#include "io.h"

struct draw
{
    QGraphicsView *gV;
    int w;
    int h;
};

struct coord_point
{
    double x;
    double y;
};

void draw_connections(points_data pts, connections_data connections, draw arg, graphics a);
void draw_line(coord_point p1, coord_point p2, graphics a, draw arg);
void my_addLine(graphics a, int x1, int x2, int y1, int y2);
coord_point get_dot(point* dots, int n);
coord_point point_transform(coord_point dot, draw arg);

#endif // DRAWING_H
