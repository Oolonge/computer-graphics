#ifndef CONSTS_H
#define CONSTS_H

#include <QGraphicsScene>

enum method_t
{
    STANDART,
    DDA,
    BRESEN_DOUBLE,
    BRESEN_INT,
    BRESEN_STEPS,
    WY
};

struct line_t
{
    QPointF start;
    QPointF end;
    QColor color;
    method_t method;
};

struct spectre_t
{
    double radius;
    double angle;
    QPointF center;
    QColor color;
    method_t method;
};

struct objects_t
{
    std::vector<line_t> lines;
    std::vector<spectre_t> spectra;
    QColor backgroundColor;
};

typedef QGraphicsScene *graphics_t;

#endif // CONSTS_H
