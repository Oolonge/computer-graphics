#include "drawing.h"

#define KX 2

void drawLine(const line& line, QPainter& paint)
{
    paint.drawLine(line.p1.x, line.p1.y, line.p2.x, line.p2.y);
}

void drawPolygon(const polygon& cut, QPainter& paint)
{
    size_t size_point = cut.points.size();
    if (size_point >= 2)
        for (size_t i = 0; i < size_point - 1; i++)
            drawLine({ cut.points[i], cut.points[i + 1] }, paint);
    if (cut.is_close)
        drawLine({cut.points[0], cut.points[size_point - 1]}, paint);
}

void drawAll(const content& data, canvas_t& scene, gv_t& view)
{
    QImage image = QImage(view->geometry().width(), view->geometry().height(), QImage::Format_ARGB32);
    QPainter p(&image);
    image.fill(Qt::white);

    p.setBrush(data.cut_color);
    p.setPen(data.cut_color);
    if (data.cutter.points.size() > 0)
        drawPolygon(data.cutter, p);

    p.setBrush(data.line_color);
    p.setPen(data.line_color);
    if (data.figure.points.size() > 0)
        drawPolygon(data.figure, p);

    QPixmap pixmap = QPixmap::fromImage(image);
    scene->clear();
    scene->addPixmap(pixmap);
}
