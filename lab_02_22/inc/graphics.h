#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "QGraphicsView"

struct graphics
{
    QGraphicsScene *scene;
    QPen pen;
};

int init_graph(graphics &a, QGraphicsView *gV);
void delete_scene(graphics &a);
void set_scene(QGraphicsView *gV, graphics &a);

#endif // GRAPHICS_H
