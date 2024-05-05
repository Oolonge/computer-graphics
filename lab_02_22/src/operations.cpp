#include "math.h"
#include "operations.h"
#include "errors.h"
#include "projection.h"
#include <math.h>
#include <QDebug>

void move_point(point& dot, move coeff)
{
    dot.x += coeff.dx;
    dot.y += coeff.dy;
}

int move_points_array(point* pts, int n, move coeff)
{
    if(!pts)
        return NO_DOTS;
    int err = 0;

    for(int i = 0; i < n; i++)
        move_point(pts[i], coeff);

    return err;
}


void scale_point(point& dot, scale coeff)
{
    dot.x *= coeff.kx;
    dot.y *= coeff.ky;
}

int scale_points_array(point* pts, int n, scale coeff)
{
    if(!pts)
        return NO_DOTS;
    int err = 0;

    for(int i = 0; i < n; i++)
        scale_point(pts[i], coeff);

    return err;
}

double d_cos(double angle)
{
    return cos(angle * M_PI / 180);
}

double d_sin(double angle)
{
    return sin(angle * M_PI / 180);
}

void x_turn_point(point& dot, double angle)
{
    if (angle == 0)
        return;

    double cos_ang = d_cos(angle);
    double sin_ang = d_sin(angle);

    double y_copy = dot.y;

    dot.y = dot.y * cos_ang - dot.x * sin_ang;
    dot.x = dot.x * cos_ang + y_copy * sin_ang;
}

void y_turn_point(point& dot, double angle)
{
    if (angle == 0)
        return;

    double cos_ang = d_cos(angle);
    double sin_ang = d_sin(angle);

    double x_copy = dot.x;

    dot.x = dot.x * cos_ang - dot.y * sin_ang;
    dot.y = dot.y * cos_ang + x_copy * sin_ang;
}

int turn_points_array(point* pts, int n, turn angle)
{
    if(!pts)
        return NO_DOTS;
    int err = 0;

    for(int i = 0; i < n; i++)
    {
        x_turn_point(pts[i], angle.ox);
        y_turn_point(pts[i], angle.oy);
    }

    return err;
}
