#include "cstdio"
#include <cstdlib>
#include "volumetric_point.h"
#include "projection.h"
#include "errors.h"

int points_alloc(points_data& pts, int len)
{
    pts.n = len + ASTR_PTS_AMOUNT * 2;
    pts.arr = (point*) calloc(pts.n, sizeof(point));

    if (!pts.arr)
        return PTR_ALLOC_ERR;

    return NONE;
}


void points_free(points_data &pts)
{
    if (pts.arr)
        free(pts.arr);
}


int read_point(point* dot, FILE* f)
{
    if (fscanf(f, "%lf%lf", &dot->x, &dot->y) != 2)
        return FILE_FORMAT_ERR;
    return NONE;
}


int read_n_points(point *dots, int n, FILE *f)
{
    int err = 0;
    for (int i = 0; i < n && !err; i++)
    {
        if (read_point(&dots[i], f))
            err = FILE_FORMAT_ERR;
    }
    return err;
}

void add_astroid_points(point *dots, int idx)
{
    double t, tmp_x, tmp_y;
    for (int i = idx; i < ASTR_PTS_AMOUNT + idx; ++i)
    {
        t = i * M_PI / (ASTR_PTS_AMOUNT + idx - 1);
        tmp_x = pow(cos(t), 3);
        tmp_y = pow(sin(t), 3);
        qDebug() << i << ":" << tmp_x << tmp_y;
        dots[i] = { .x = tmp_x, .y = tmp_y};
        dots[i + ASTR_PTS_AMOUNT] = {.x = -tmp_x, .y = -tmp_y};
    }
}

int process_points(points_data &pts, FILE *f)
{
    int n;
    int err = 0;

    err = read_amount(&n, f);

    if (!err)
    {
        err = points_alloc(pts, n);

        if (err)
            return err;

        err = read_n_points(pts.arr, n, f);

        if (err)
        {
            points_free(pts);
            return err;
        }
        add_astroid_points(pts.arr, n);
    }
    return err;
}
