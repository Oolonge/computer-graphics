#include "cstdio"
#include <cstdlib>
#include "projection.h"
#include "errors.h"
#include "volumetric_point.h"
#include "io.h"
#include "drawing.h"
#include "graphics.h"
#include "operations.h"
#include "qdebug.h"

projection& init()
{
    static projection fig;

    fig.points.n = 0;
    fig.points.arr = NULL;

    fig.connections.n = 0;
    fig.connections.arr = NULL;

    return fig;
}


void empty_figure(projection& fig)
{
    fig.points.n = 0;
    points_free(fig.points);

    fig.connections.n = 0;
    connections_free(fig.connections);
}

void copy_figure(projection& fig, projection& tmp)
{
    fig.points.n = tmp.points.n;
    fig.points.arr = tmp.points.arr;

    fig.connections.n = tmp.connections.n;
    fig.connections.arr = tmp.connections.arr;
}

int fill_figure_fields(projection& fig, FILE *f)
{
    int err = process_points(fig.points, f);
    if (!err)
    {
        err = process_connections(fig.connections, f);
        if (err != NONE)
            points_free(fig.points);
    }
    return err;
}

int load_figure_from_file(projection& fig, const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f)
        return FILE_NOT_FOUND;
    projection fig_tmp = init();

    int err = fill_figure_fields(fig_tmp, f);
    fclose(f);

    if (err)
        return err;

    if (!err)
    {
        empty_figure(fig);
        copy_figure(fig, fig_tmp);
    }

    return err;
}

int draw_figure(projection fig, draw arg)
{
    graphics a;

    int err = init_graph(a, arg.gV);
    if (err)
        return err;

    draw_connections(fig.points, fig.connections, arg, a);

    a.scene->setSceneRect(QRectF(QPointF(0, 0), QSizeF(arg.w, arg.h)));
    set_scene(arg.gV, a);

    return err;
}

int move_figure(projection& fig, move coeff)
{
    return move_points_array(fig.points.arr, fig.points.n, coeff);
}

int scale_figure(projection& fig, scale coeff)
{
    return scale_points_array(fig.points.arr, fig.points.n, coeff);
}

int turn_figure(projection& fig, turn coeff)
{
    return turn_points_array(fig.points.arr, fig.points.n, coeff);
}
