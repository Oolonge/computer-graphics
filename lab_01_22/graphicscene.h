#ifndef GRAPHICSCENE_H
#define GRAPHICSCENE_H

#include <QStandardItemModel>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QObject>
#include <math.h>
#include <QDebug>
#include <QVector2D>

class GraphicScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicScene(double x, double y, double w, double h, bool state, QObject *parent = nullptr);

    // grid properties
    void setGridVisibility(bool value);
    bool gridIsVisible(void);

    // point properties
    void addPoint(QPointF point);
    QVector<QPointF> getPoints(void);
    void removeAllPoints(void);

    // model for the points table
    QStandardItemModel* pointsModel(void);

    // plane and coord properties
    void setPlane(double x, double y, double w, double h, bool update = true);
    void setPlane(QRectF rect, bool update = true);
    void setPlane(QPointF topLeft, double w, double h, bool update = true);
    QRectF getPlane(void);

    // graphicsWindow properties
    void setGraphicsWindow(double x, double y, double w, double h, bool update = true);
    void setGraphicsWindow(QRectF rect);
    QRectF getGraphicsWindow(void);

    // coefficients
    double getCX(void);
    double getCY(void);
    void setCX(double c);
    void setCY(double c);

    QPointF toPlaneCoords(QPointF windowCoords);
    QPointF toWindowCoords(QPointF planeCoords);

    // zoom properties
    void zoomAtPercent(double zoom);

    bool showSolution = false;

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
    QRectF plane, graphicsWindow, originalGraphicsWindow;
    QVector<QPointF> points;
    QVector<QPointF> res_triangle;
    bool gridVisible;
    double cX, cY;
    QPointF dragStartPos;
    bool isDragged = false;
    QSizeF originalSize;
    double zoomPercent;
    QPointF bisectorPoint;
    int bisectorFrom;

    // for pointsView
    mutable QStandardItemModel* pointsModel_ = nullptr;

    // methods
    void computeCoefficients(void);

    void drawXAxis(QPainter *painter);
    void drawYAxis(QPainter *painter);
    void drawCenter(QPainter *painter);
    void drawPoint(QPainter *painter, QPointF point, double k);
    void drawPointConnections(QPainter *painter, QVector<QPointF> pointsToConnect);
    void removeIntersectingPoint(QPointF point);

    double getDistance(QPointF a, QPointF b);

    bool isDuplicate(QVector<QPointF> points, QPointF point);

public slots:

    //solution, for "algorithm.h/.cpp"
    bool isDegenerate(qreal a, qreal b, qreal c);
    void initTriangle(QVector<QPointF> &triangle);
    void calculateVectors(const QVector<QPointF> &triangle,
                          QVector2D &vecA, QVector2D &vecB, QVector2D &vecC,
                          qreal &a, qreal &b, qreal &c);
    void compareMins(const QVector<QPointF> &triangle,
                     const QVector2D &vecAK, const QVector2D &vecBK, const QVector2D &vecCK,
                     qreal &bMin, qreal &bMax, const qreal ak, const qreal bk);
    int solveProblem(void);
    //ends here

    void updatePointsModel(void);

    void resetZoom(void);
};

#endif // GRAPHICSCENE_H
