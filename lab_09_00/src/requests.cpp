#include "requests.h"
#include "cut.h"
#include "drawing.h"
#include "figure.h"

void cutDraw(content& data, canvas_t& scene, gv_t& view)
{
    cut(data);
    QImage image = QImage(view->geometry().width(), view->geometry().height(), QImage::Format_ARGB32);
    QPainter p(&image);
    image.fill(Qt::transparent);
    p.setPen(data.visible_color);
    p.setBrush(data.visible_color);
    drawPolygon(data.visible_figure, p);
    QPixmap pixmap = QPixmap::fromImage(image);
    scene->addPixmap(pixmap);
}

int request_handle(request& req)
{
    int rc = 0;
    switch (req.operation) {
    case ADD_POINT:
        rc = addPoint(req.cut_flag, req.p, req.data);
        break;
    case CUT:
        cutDraw(req.data, req.scene, req.view);
        break;
    case DRAW_ALL:
        drawAll(req.data, req.scene, req.view);
        break;
    }
    return rc;
}
