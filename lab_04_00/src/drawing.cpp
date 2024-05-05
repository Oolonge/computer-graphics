#include "drawing.h"
#include "algorithms.h"
#include <cmath>

void drawing_axes(canvas_t &scene)
{
    QPen pen = QPen(Qt::black, 2);
    // Oy
    scene->addLine(0, 0, 0, 400, pen);

    // Y-arrow
    scene->addLine(-6, 392, 0, 402, pen);
    scene->addLine(0, 402, 6, 392, pen);

    // Y
    scene->addLine(-6, 412, 0, 420, pen);
    scene->addLine(0, 420, 6, 412, pen);
    scene->addLine(0, 420, 0, 428, pen);

    // Ox
    scene->addLine(0, 0, 400, 0, pen);

    // X-arrow
    scene->addLine(400, 0, 392, 6, pen);
    scene->addLine(400, 0, 392, -6, pen);

    // X
    scene->addLine(410, -6, 418, 6, pen);
    scene->addLine(418, -6, 410, 6, pen);
}

void drawPixel(canvas_t &scene, const double &x, const double &y, const QColor &color)
{
    QPen pen = QPen(QColor(0,0,0,0));
    QBrush brush = QBrush(color);
    scene->addRect(round(x), round(y), 1, 1, pen, brush);
}

void drawAll(canvas_t &scene, gv_t &gv, const content_t &data)
{
    scene->clear();
    gv->setBackgroundBrush(data.back_color);
    drawing_axes(scene);

    for (size_t i = 0; i < data.figures.size(); i++)
    {
        if (data.figures[i].type == CIRCLE)
            drawCircle(scene, data.figures[i], true);
        else
            drawEllipse(scene, data.figures[i], true);
    }

    for (size_t i = 0; i < data.spectrums.size(); i++)
    {
        if (data.spectrums[i].type == CIRCLE)
            drawCircleSpectrum(scene, data.spectrums[i]);
        else
            drawElipseSpectrum(scene, data.spectrums[i]);
    }
}

void drawCircle(canvas_t &scene, const figure_t &data, const bool &drawingFlag)
{
    switch (data.algorithm)
    {
        case STANDART:
            circleStandard(scene, data);
            break;
        case CANONICAL:
            circleCanonical(scene, data, drawingFlag);
            break;
        case PARAMETRIC:
            circleParametrical(scene, data, drawingFlag);
            break;
        case BRESEN:
            circleBresen(scene, data, drawingFlag);
            break;
        case MIDDLE_POINT:
            circleMiddlePoint(scene, data, drawingFlag);
            break;
    }
}

void drawEllipse(canvas_t &scene, const figure_t &data, const bool &drawingFlag)
{
    switch (data.algorithm)
    {
        case STANDART:
            ellipseStandard(scene, data);
            break;
        case CANONICAL:
            ellipseCanonical(scene, data, drawingFlag);
            break;
        case PARAMETRIC:
            ellipseParametrical(scene, data, drawingFlag);
            break;
        case BRESEN:
            ellipseBresen(scene, data, drawingFlag);
            break;
        case MIDDLE_POINT:
            ellipseMiddlePoint(scene, data, drawingFlag);
            break;
    }
}

void drawCircleSpectrum(canvas_t &scene, const spectrum_t &spectrum)
{
    figure_t circle;
    circle.center = spectrum.center;
    circle.color = spectrum.color;
    circle.algorithm = spectrum.algorithm;
    for (int i = 0; i < spectrum.n; i++)
    {
        circle.ra = spectrum.ra + i * spectrum.dra;
        drawCircle(scene, circle, true);
    }
}

void drawElipseSpectrum(canvas_t &scene, const spectrum_t &spectrum)
{
    figure_t ellispe;
    ellispe.center = spectrum.center;
    ellispe.color = spectrum.color;
    ellispe.algorithm = spectrum.algorithm;
    for (int i = 0; i < spectrum.n; i++)
    {
        ellispe.ra = spectrum.ra + i * spectrum.dra;
        ellispe.rb = spectrum.rb + i * spectrum.drb;
        drawEllipse(scene, ellispe, true);
    }
}

void drawCircleReflect(canvas_t &scene, const QPointF &point, const QPointF &center, const QColor &color)
{
    drawPixel(scene, point.x(), point.y(), color);
    drawPixel(scene, 2 * center.x() - point.x(), point.y(), color);
    drawPixel(scene, point.x(), 2 * center.y() - point.y(), color);
    drawPixel(scene, 2 * center.x() - point.x(), 2 * center.y() - point.y(), color);
    drawPixel(scene, point.y() + center.x() - center.y(),
             point.x() + center.y() - center.x(), color);
    drawPixel(scene, -point.y() + center.x() + center.y(),
             point.x() + center.y() - center.x(), color);
    drawPixel(scene, point.y() + center.x() - center.y(),
             -point.x() + center.y() + center.x(), color);
    drawPixel(scene, -point.y() + center.x() + center.y(),
             -point.x() + center.x() + center.y(), color);

}

void drawEllipseReflect(canvas_t &scene, const QPointF &point, const QPointF &center, const QColor &color)
{
    drawPixel(scene, point.x(), point.y(), color);
    drawPixel(scene, 2 * center.x() - point.x(), point.y(), color);
    drawPixel(scene, point.x(), 2 * center.y() - point.y(), color);
    drawPixel(scene, 2 * center.x() - point.x(), 2 * center.y() - point.y(), color);
}
