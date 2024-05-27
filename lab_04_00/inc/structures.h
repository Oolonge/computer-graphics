#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <QPointF>
#include <QColor>
#include <QGraphicsScene>
#include <QGraphicsView>

enum algorithm_t
{
    STANDART,
    CANONICAL,
    PARAMETRIC,
    BRESEN,
    MIDDLE_POINT,
};


enum figure_type_t
{
    CIRCLE,
    ELLIPSE,
};

struct figure_t
{
    algorithm_t algorithm;
    figure_type_t type;
    QPoint center;
    double ra;
    double rb;
    QColor color;
};

struct spectrum_t
{
    QPoint center;
    figure_type_t type;
    double ra;
    double rb;
    double dra;
    double drb;
    int n;
    algorithm_t algorithm;
    QColor color;
};

struct content_t
{
    std::vector<figure_t> figures;
    std::vector<spectrum_t> spectrums;
    QColor back_color;
};

typedef QGraphicsScene *canvas_t;
typedef QGraphicsView *gv_t;

void copy(struct content_t **a, struct content_t *b);

#endif // STRUCTURES_H
