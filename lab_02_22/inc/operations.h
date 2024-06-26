#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "volumetric_point.h"

struct move
{
    int dx;
    int dy;
};

struct scale
{
    double kx;
    double ky;
};

struct turn
{
    int ox;
    int oy;
};

void move_point(point& dot, move coeff);
int move_points_array(point* pts, int n, move coeff);

void scale_point(point& dot, scale coeff);
int scale_points_array(point* pts, int n, scale coeff);

double d_cos(double angle);
double d_sin(double angle);

void x_turn_point(point& dot, double angle);
void y_turn_point(point& dot, double angle);
void z_turn_point(point& dot, double angle);
int turn_points_array(point* pts, int n, turn coeff);

#endif // OPERATIONS_H
