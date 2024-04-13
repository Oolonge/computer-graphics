#include "algorithms.h"
#include <cmath>

static int sign(double x)
{
    if (x < 0)
        return -1;
    if (x > 0)
        return 1;
    return 0;
}

double fpart(double x)
{
    return x - int(x);
}

double ipart(double x)
{
    return x - fpart(x);
}

double rfpart(double x)
{
    return 1 - fpart(x);
}

double mround(double x)
{
    return ipart(x + 0.5);
}

QColor update(QColor color, double intensity)
{
    int r = color.red();
    int g = color.green();
    int b = color.blue();

    int res;
    res = 255 * intensity;
    if (res > 255)
        res = 255;
    else if (res < 0)
        res = 0;

    QColor clr = QColor(r, g, b, res);
    return clr;
}

void draw_pixel(double x, double y, graphics_t scene, QColor color)
{
    QPen pen = QPen(color);
    QBrush brush = QBrush(color);
    scene->addRect(x, y, 1, 1, pen, brush);
}

void standart_line(line_t &line, graphics_t scene)
{
    QLineF l = QLineF(line.start, line.end);
    scene->addLine(l, QPen(line.color, 1));
}

int dda_line(line_t &line, graphics_t scene, bool drawingFlag=false, bool countStepsFlag=false)
{
    int iX1 = round(line.start.x());
    int iY1 = round(line.start.y());
    int iX2 = round(line.end.x());
    int iY2 = round(line.end.y());

    int deltaX = abs(iX2 - iX1);
    int deltaY = abs(iY2 - iY1);

    int length = std::max(deltaX, deltaY);

    if (length == 0)
        if (drawingFlag)
            draw_pixel(iX1, iY1, scene, line.color);

    double dX = (line.end.x() - line.start.x()) / length;
    double dY = (line.end.y() - line.start.y()) / length;

    double x = line.start.x();
    double y = line.start.y();

    double buf_x = x, buf_y = y;
    int steps = 1;

    for (int i = 0; i < length; i++)
    {
        if (drawingFlag)
            draw_pixel(round(x), round(y), scene, line.color);

        x += dX;
        y += dY;

        if (countStepsFlag)
        {
            if (round(x) != round(buf_x) && round(y) != round(buf_y))
                steps++;

            buf_x = x;
            buf_y = y;
        }
    }

    return steps;
}

int bresen_double_line(line_t &line, graphics_t scene, bool drawingFlag=false, bool countStepsFlag=false)
{
    double x = round(line.start.x());
    double y = round(line.start.y());

    double dx = line.end.x() - line.start.x();
    double dy = line.end.y() - line.start.y();

    int sx = sign(dx);
    int sy = sign(dy);

    dx = abs(dx);
    dy = abs(dy);

    int change = 0;
    if (dy >= dx)
        change = 1;

    if (change)
        std::swap(dx, dy);

    double m = dy / dx;
    double e = m - 0.5;

    double buf_x = x, buf_y = y;
    int steps = 1;

    for (int i = 0; i <= dx; i++)
    {
        if (drawingFlag)
            draw_pixel(x, y, scene, line.color);

        if (e >= 0)
        {
            if (change == 0)
                y += sy;
            else
                x += sx;
            e--;
        }

        if (e <= 0)
        {
            if (change == 0)
                x += sx;
            else
                y += sy;
            e += m;
        }

        if (countStepsFlag)
        {
            if (buf_x != x && buf_y != y)
                steps++;

            buf_x = x;
            buf_y = y;
        }
    }

    return steps;
}

int bresen_int_line(line_t &line, graphics_t scene, bool drawingFlag=false, bool countStepsFlag=false)
{
    int x = round(line.start.x());
    int y = round(line.start.y());

    int dx = line.end.x() - line.start.x();
    int dy = line.end.y() - line.start.y();

    int sx = sign(dx);
    int sy = sign(dy);

    dx = abs(dx);
    dy = abs(dy);

    int change = 0;
    if (dy >= dx)
        change = 1;

    if (change)
        std::swap(dx, dy);

    int m = 2 * dy;
    int m1 = 2 * dx;
    int e = m - dx;

    int buf_x = x, buf_y = y;
    int steps = 1;

    for (int i = 0; i <= dx; i++)
    {
        if (drawingFlag)
            draw_pixel(x, y, scene, line.color);

        if (e >= 0)
        {
            if (change == 0)
                y += sy;
            else
                x += sx;
            e -= m1;
        }
        if (e <= 0)
        {
            if (change == 0)
                x += sx;
            else
                y += sy;
            e += m;
        }

        if (countStepsFlag)
        {
            if (buf_x != x && buf_y != y)
                steps++;

            buf_x = x;
            buf_y = y;
        }
    }

    return steps;
}

int bresen_steps_line(line_t &line, graphics_t scene, bool drawingFlag=false, bool countStepsFlag=false)
{
    double x = round(line.start.x());
    double y = round(line.start.y());

    double dx = line.end.x() - line.start.x();
    double dy = line.end.y() - line.start.y();

    int sx = sign(dx);
    int sy = sign(dy);

    dx = abs(dx);
    dy = abs(dy);

    int change;
    if (dx > dy)
        change = 0;
    else
    {
        change = 1;
        std::swap(dx, dy);
    }

    double m = dy / dx;
    double e = 0.5;
    QColor color1 = update(line.color, e);

    if (drawingFlag)
        draw_pixel(x, y, scene, color1);

    double W = 1 - m;

    double buf_x = x, buf_y = y;
    int steps = 1;

    for (int i = 0; i <= dx; i++)
    {
        if (e < W)
        {
            if (change == 0)
                x += sx;
            else
                y += sy;
            e += m;
        }
        else
        {
            x += sx;
            y += sy;
            e -= W;
        }

        color1 = update(color1, e);
        if (drawingFlag)
            draw_pixel(x, y, scene, color1);

        if (countStepsFlag)
        {
            if (buf_x != x && buf_y != y)
                steps++;

            buf_x = x;
            buf_y = y;
        }
    }

    return steps;
}

int wy_line(line_t &line, graphics_t scene, bool drawingFlag=false, bool countStepsFlag=false)
{
    QColor c1, c2;
    double x0 = line.start.x();
    double y0 = line.start.y();

    double x1 = line.end.x();
    double y1 = line.end.y();

    bool steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    double dx = x1 - x0;
    double dy = y1 - y0;
    double gradient = (dx == 0) ? 1 : dy / dx;

    int xpx11;
    double intery;
    {
        double xend = round(x0);
        double yend = y0 + gradient * (xend - x0);
        double xgap = rfpart(x0 + 0.5);
        xpx11 = int(xend);
        int ypx11 = ipart(yend);

        c1 = update(line.color, rfpart(yend) * xgap);
        c2 = update(line.color, fpart(yend) * xgap);
        if (drawingFlag)
        {
            if (steep)
            {
                draw_pixel(ypx11, xpx11, scene, c1);
                draw_pixel(ypx11 + 1, xpx11, scene, c2);
            } else
            {
                draw_pixel(xpx11, ypx11, scene, c1);
                draw_pixel(xpx11, ypx11 + 1, scene, c2);
            }
        }

        intery = yend + gradient;
    }

    int xpx12;
    {
        double xend = round(x1);
        double yend = y1 + gradient * (xend - x1);
        double xgap = rfpart(x1 + 0.5);
        xpx12 = int(xend);
        int ypx12 = ipart(yend);

        c1 = update(line.color, rfpart(yend) * xgap);
        c2 = update(line.color, fpart(yend) * xgap);
        if (drawingFlag)
        {
            if (steep)
            {
                draw_pixel(ypx12, xpx12, scene, c1);
                draw_pixel(ypx12 + 1, xpx12, scene, c2);
            } else
            {
                draw_pixel(xpx12, ypx12, scene, c1);
                draw_pixel(xpx12, ypx12 + 1, scene, c2);
            }
        }
    }

    int steps = 0;
    for (int x = xpx11 + 1; x < xpx12; x++)
    {
        c1 = update(line.color, rfpart(intery));
        c2 = update(line.color, fpart(intery));
        if (drawingFlag)
        {
            if (steep)
            {
                draw_pixel(ipart(intery), x, scene, c1);
                draw_pixel(ipart(intery) + 1, x, scene, c2);
            }
            else
            {
                draw_pixel(x, ipart(intery), scene, c1);
                draw_pixel(x, ipart(intery) + 1, scene, c2);
            }
        }

        if (countStepsFlag && x < xpx12)
            if (ipart(intery) != ipart(intery + gradient))
                steps++;

        intery += gradient;
    }

    return steps;
}
