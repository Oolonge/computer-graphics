#include "drawing.h"
#include "fill.h"

#define COEF 2

void drawPoint(const point &point, QPainter &p)
{
    p.drawRect(point.x - COEF / 2, point.y - COEF / 2, COEF, COEF);
}

void drawConnection(const point &p1, const point &p2, QPainter &p)
{
    drawPoint(p1, p);
    drawPoint(p2, p);
    p.drawLine(p1.x, p1.y, p2.x, p2.y);
}

// функция отрисовки точек (без окружностей)
void drawPoints(canvas_t &scene, gv_t &gv, const bool &is_sel, const point &selected_p, const content &data)
{
    scene->clear();
//    gv->setBackgroundBrush(data.back_color);
    QImage image = QImage(gv->geometry().width(), gv->geometry().height(), QImage::Format_ARGB32);
    QPainter p(&image);
    image.fill(data.back_color);
//    image.fill(Qt::transparent);

    figure f;
    for (size_t i = 0; i < data.figures.size(); i++)
    {
        f = data.figures[i];
        p.setPen(f.line_color);
        p.setBrush(f.line_color);
        size_t size = f.main_figure.size();
        if (size == 1)
            drawPoint(f.main_figure[0], p);
        else if (size > 1)
        {
            for (size_t j = 0; j < size - 1; j++)
                drawConnection(f.main_figure[j], f.main_figure[j + 1], p);
            if (f.closed_figure_flag)
                drawConnection(f.main_figure[0], f.main_figure[f.main_figure.size() - 1], p);
            for (size_t j = 0; j < f.holes.size(); j++)
            {
                size_t size_h = f.holes[j].points.size();
                if (size_h == 1)
                    drawPoint(f.holes[j].points[0], p);
                else if (size_h > 1)
                {
                    for (size_t k = 0; k < f.holes[j].points.size() - 1; k++)
                        drawConnection(f.holes[j].points[k], f.holes[j].points[k + 1], p);
                    if (f.holes[j].closed_hole_flag)
                        drawConnection(f.holes[j].points[0], f.holes[j].points[f.holes[j].points.size() - 1], p);
                }
            }
        }
    }
    if (is_sel)
    {
        p.setBrush(Qt::red);
        p.setPen(Qt::red);

        drawPoint(selected_p, p);
    }

    QPixmap pixmap = QPixmap::fromImage(image);
    scene->addPixmap(pixmap);
}


void selectPoint(canvas_t &scene, gv_t &gv, const point &selected_p, const content &data)
{
    QImage image = QImage(gv->geometry().width(), gv->geometry().height(), QImage::Format_ARGB32);
    QPainter p(&image);
    image.fill(Qt::transparent);

    figure f;
    for (size_t i = 0; i < data.figures.size(); i++)
    {
        f = data.figures[i];
        p.setPen(f.line_color);
        p.setBrush(f.line_color);

        for (size_t j = 0; j < f.main_figure.size(); j++)
            drawPoint(f.main_figure[j], p);
        for (size_t j = 0; j < f.holes.size(); j++)
            for (size_t k = 0; k < f.holes[j].points.size(); k++)
                drawPoint(f.holes[j].points[k], p);
    }

    p.setBrush(Qt::red);
    p.setPen(Qt::red);

    drawPoint(selected_p, p);

    QPixmap pixmap = QPixmap::fromImage(image);
    scene->addPixmap(pixmap);
}

