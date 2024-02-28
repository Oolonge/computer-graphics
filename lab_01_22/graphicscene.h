#ifndef GRAPHICSCENE_H
#define GRAPHICSCENE_H

#include <QStandardItemModel>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QObject>
#include <math.h>

class GraphicScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicScene(double x, double y, double w, double h, bool state, QObject *parent = nullptr);

    // visibility properties
    void setGridVisibility(bool value);
    bool gridIsVisible(void);

    // point properties
    void addPoint(QPointF point);
    std::vector<QPointF> getPoints(void);
    void removeAllPoints(void);

    // model for the points table
    QStandardItemModel* pointsModel(void);

    // plane coordinates properties
    void setPlane(double x, double y, double w, double h, bool update = true);
    void setPlane(QPointF topLeft, double w, double h, bool update = true);
    QRectF getPlane(void);

    // graphicsWindow properties
    void setGraphicsWindow(double x, double y, double w, double h, bool update = true);
    void setGraphicsWindow(QRectF rect);
    QRectF getGraphicsWindow(void);

    // coefficient properties
    void setCX(double c);
    void setCY(double c);
    double getCX(void);
    double getCY(void);

    QPointF toPlaneCoords(QPointF windowCoords);
    QPointF toWindowCoords(QPointF planeCoords);

    // zoom properties
    void zoomAtPercent(double zoom);

signals:
    void zoomChanged(double value);
    void pointsUpdated(void);

protected:
    // overrides
    virtual void drawBackground(QPainter *painter, const QRectF &rect) override;
    virtual void drawForeground(QPainter *painter, const QRectF &rect) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    virtual void wheelEvent(QGraphicsSceneWheelEvent *wheelEvent) override;

    // attributes
    QRectF plane, graphicsWindow;
    std::vector<QPointF> points;
    bool gridVisible;
    double cX, cY;
    QPointF dragStartPos;
    bool isDragged = false;
    QSizeF originalSize;
    double zoomPercent;

    // for points table
    mutable QStandardItemModel* pointsModel_ = nullptr;

    // methods
    void computeCoefficients(void);

    void drawXAxis(QPainter *painter);
    void drawYAxis(QPainter *painter);
    void drawCenter(QPainter *painter);
    void drawPoint(QPainter *painter, QPointF point, double k);
    void removeIntersectingPoint(QPointF point);

    double getDistance(QPointF a, QPointF b);

public slots:
    void updatePointsModel(void);
};

#endif // GRAPHICSCENE_H
