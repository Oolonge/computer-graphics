#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <QGraphicsScene>
#include <QGraphicsView>

typedef QGraphicsScene *canvas_t;
typedef QGraphicsView *gv_t;

struct point
{
    int x;
    int y;
};

struct colors
{
    QColor line;
    QColor fill;
};

struct indexes
{
    int fig;
    int hole;
    size_t index;
};

struct node
{
    double x;
    double dx;
    int dy;
};

struct hole
{
    std::vector<point> points;
    bool closed_hole_flag;
};

struct figure
{
    std::vector<point> main_figure;
    std::vector<hole> holes;
    QColor line_color;
    QColor fill_color;
    bool closed_figure_flag;
};

struct content
{
    std::vector<figure> figures;
    QColor back_color;
    int n_figures;
    int n_holes;
};

#endif // STRUCTURES_H
