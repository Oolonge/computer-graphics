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
    for (size_t i = 0; i < data.visible_lines.size(); i++)
        drawCutLine(data.visible_lines[i], p);
    QPixmap pixmap = QPixmap::fromImage(image);
    scene->addPixmap(pixmap);
}

int handle_request(request& req)
{
    int rc = 0;
    switch (req.operation) {
    case ADD_POINT:
        rc = addPoint(req.cut_flag, req.p, req.number, req.data);
        break;
    case CUT:
        cutDraw(req.data, req.scene, req.view);
        break;
    case DRAW_ALL:
        DrawAll(req.data, req.scene, req.view);
        break;
    }
    return rc;
}
