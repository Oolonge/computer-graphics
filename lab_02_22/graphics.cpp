#include "graphics.h"
#include "errors.h"

int init_graph(graphics &a, QGraphicsView *gV)
{
    a.scene = new QGraphicsScene(gV);
    if (!a.scene)
        return PTR_ALLOC_ERR;

    a.pen = QPen(Qt::black);

    return 0;
}

void delete_scene(graphics &a)
{
    delete a.scene;
}

void set_scene(QGraphicsView *gV, graphics &a)
{
    QGraphicsScene *prev = gV->scene();
    delete prev;
    gV->setScene(a.scene);
}
