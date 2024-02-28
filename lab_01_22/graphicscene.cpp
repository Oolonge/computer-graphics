#include "graphicscene.h"

GraphicScene::GraphicScene(double x, double y, double w, double h, bool isVisible, QObject *parent)
    : QGraphicsScene{parent}
{
    // std::cout<< "constructor" << std::endl;
    this->setGridVisibility(isVisible);
    this->setPlane(x, y, w, h, false);
    this->setGraphicsWindow(x, y, w, h, false);
    this->originalSize = QSizeF(w, h);
    this->zoomPercent = 100;
}

void GraphicScene::setCX(double c)
{
    // std::cout<< "setCX" << std::endl;
    this->cX = c;
}

void GraphicScene::setCY(double c)
{
    // std::cout<< "setCY" << std::endl;
    this->cY = c;
}

double GraphicScene::getCX(void)
{
    // std::cout<< "getCX" << std::endl;
    return this->cX;
}

double GraphicScene::getCY(void)
{
    // std::cout<< "getCY" << std::endl;
    return this->cY;
}

void GraphicScene::setGridVisibility(bool value)
{
    // std::cout<< "setGridVisibility" << std::endl;
    gridVisible = value;
    this->update();
}

bool GraphicScene::gridIsVisible(void)
{
    // std::cout<< "gridIsVisible" << std::endl;
    return gridVisible;
}

void GraphicScene::setPlane(double x, double y, double w, double h, bool update)
{
    // std::cout<< "setPlane2" << std::endl;
    this->plane = QRectF(x, y, w, h);
    this->computeCoefficients();

    if (update)
    {
        this->update();
    }
}

void GraphicScene::setPlane(QPointF topLeft, double w, double h, bool update)
{
    // std::cout<< "setPlane1" << std::endl;
    this->plane = QRectF(topLeft.x(), topLeft.y(), w, h);
    this->computeCoefficients();

    if (update)
    {
        // std::cout<< "updating after plane change" << std::endl;
        this->update();
    }
}

QRectF GraphicScene::getPlane(void)
{
    // std::cout<< "getPlane" << std::endl;
    return this->plane;
}

void GraphicScene::setGraphicsWindow(double x, double y, double w, double h, bool update)
{
    // std::cout<< "getGraphicsWindow coords" << std::endl;
    this->graphicsWindow = QRectF(x, y, w, h);
    this->computeCoefficients();

    if (update)
    {
        this->update();
    }
}

void GraphicScene::setGraphicsWindow(QRectF rect)
{
    // std::cout<< "setGraphicsWindow" << std::endl;
    this->graphicsWindow = rect;
    this->computeCoefficients();
}

QRectF GraphicScene::getGraphicsWindow(void)
{
    // // std::cout<< "getGraphicsWindow" << std::endl;
    return this->graphicsWindow;
}

void GraphicScene::computeCoefficients(void)
{
    // std::cout<< "computeCoefficients" << std::endl;
    if (!this->plane.isValid() || !this->graphicsWindow.isValid())
    {
        return;
    }

    this->setCX(this->graphicsWindow.width() / this->plane.width());
    this->setCY(this->graphicsWindow.height() / this->plane.height());

    // std::cout<< "cx: " << this->cX << " cy: " << this->cY << std::endl;
}

QPointF GraphicScene::toPlaneCoords(QPointF windowCoords)
{
    // std::cout<< "toPlaneCoords" << std::endl;
    QPointF planeCoords = windowCoords;

    if (this->cX == 0 || this->cY == 0)
    {
        throw new std::runtime_error("Коэффициент равен нулю, невозможно перевести координаты");
    }

    planeCoords.setX((windowCoords.x() - this->graphicsWindow.topLeft().x()) / this->cX + this->plane.topLeft().x());
    planeCoords.setY((windowCoords.y() - this->graphicsWindow.topLeft().y()) / this->cY + this->plane.topLeft().y());

    return planeCoords;
}

QPointF GraphicScene::toWindowCoords(QPointF planeCoords)
{
    // std::cout<< "toWindowCoords" << std::endl;
    QPointF windowCoords = planeCoords;

    windowCoords.setX((planeCoords.x() - this->plane.topLeft().x()) * this->cX + this->graphicsWindow.topLeft().x());
    windowCoords.setY((planeCoords.y() - this->plane.topLeft().y()) * this->cY + this->graphicsWindow.topLeft().y());

    return windowCoords;
}

void GraphicScene::drawForeground(QPainter *painter, const QRectF &rect)
{
    // std::cout<< "drawForeground" << std::endl;
    this->setGraphicsWindow(rect);
    painter->setPen(Qt::blue);
    painter->setBrush(Qt::blue);
    for (auto point : this->points)

    {
        this->drawPoint(painter, point, 0.008);
    }
}

void GraphicScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    // update graphics
    this->setGraphicsWindow(rect);

    // white background
    painter->fillRect(this->getGraphicsWindow(), Qt::white);

    // draw lines and center
    painter->setPen(Qt::black);
    bool intersectsX = this->plane.top() <= 0 && this->plane.bottom() >= 0;
    bool intersectsY = this->plane.left() <= 0 && this->plane.right() >= 0;

    if (intersectsX)
    {
        this->drawXAxis(painter);
    }
    if (intersectsY)
    {
        this->drawYAxis(painter);
    }
    if (intersectsX && intersectsY)
    {
        this->drawCenter(painter);
    }
    if (!this->gridIsVisible())
    {
        return;
    }

    painter->setPen(Qt::gray);
    painter->setBrush(Qt::gray);
    // draw grid
    for (long x = this->plane.left() - 1; x < this->plane.right() + 1; x++)
    {
        QPointF top = this->toWindowCoords(QPointF(x, this->plane.top()));
        QPointF bottom = this->toWindowCoords(QPointF(x, this->plane.bottom()));
        painter->drawLine(top, bottom);
    }

    for (long y = this->plane.top() - 1; y < this->plane.bottom() + 1; y++)
    {
        QPointF left = this->toWindowCoords(QPointF(this->plane.left(), y));
        QPointF right = this->toWindowCoords(QPointF(this->plane.right(), y));
        painter->drawLine(left, right);
    }

    painter->setPen(Qt::black);
    if (intersectsX)
    {
        this->drawXAxis(painter);
    }
    if (intersectsY)
    {
        this->drawYAxis(painter);
    }
    if (intersectsX && intersectsY)
    {
        this->drawCenter(painter);
    }
}

void GraphicScene::drawXAxis(QPainter *painter)
{
    // std::cout<< "drawXAxis" << std::endl;
    painter->setPen(Qt::black);
    QPointF xAxisStart = this->toWindowCoords(QPointF(this->plane.left(), 0));
    QPointF xAxisEnd = this->toWindowCoords(QPointF(this->plane.right(), 0));
    painter->drawLine(xAxisStart, xAxisEnd);
}

void GraphicScene::drawYAxis(QPainter *painter)
{
    // std::cout<< "drawYAxis" << std::endl;
    painter->setPen(Qt::black);
    QPointF yAxisStart = this->toWindowCoords(QPointF(0, this->plane.top()));
    QPointF yAxisEnd = this->toWindowCoords(QPointF(0, this->plane.bottom()));
    painter->drawLine(yAxisStart, yAxisEnd);
}

void GraphicScene::drawCenter(QPainter *painter)
{
    // std::cout<< "drawCenter" << std::endl;
    painter->setPen(Qt::red);
    painter->setBrush(Qt::red);
    QPointF center = QPointF(0, 0);

    this->drawPoint(painter, center, 0.005);
}

/**
 * @brief Draws a point on coordinate plane
 * @param painter doesn't change pen/brush color itself
 * @param point plane coordinates
 */
void GraphicScene::drawPoint(QPainter *painter, QPointF point, double k)
{
    // std::cout<< "drawPoint" << std::endl;
    QPointF convertedPoint = this->toWindowCoords(point);
    double rx = this->graphicsWindow.width() * k;
    double ry = this->graphicsWindow.height() * k;
    painter->drawEllipse(convertedPoint, rx, ry);
}

void GraphicScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    // std::cout<< "Mouse press" << std::endl;
    QPointF windowPoint = mouseEvent->scenePos();
    Qt::MouseButton buttonPressed = mouseEvent->button();
    if (buttonPressed == Qt::MouseButton::LeftButton)
    {
        this->addPoint(this->toPlaneCoords(windowPoint));
    }
    else if (buttonPressed == Qt::MouseButton::MiddleButton)
    {
        if (!this->isDragged)
        {
            this->dragStartPos = this->toPlaneCoords(windowPoint);
            this->isDragged = true;
        }
    }
    else if (buttonPressed == Qt::MouseButton::RightButton)
    {
        this->removeIntersectingPoint(this->toPlaneCoords(windowPoint));
    }
}

void GraphicScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    // // std::cout<< "Mouse move" << std::endl;
    // // std::cout<< "mouse buttons: " << mouseEvent->buttons().toInt() << std::endl;
    if (mouseEvent->buttons() & Qt::MouseButton::MiddleButton)
    {
        // std::cout<< "Dragging" << std::endl;
        QPointF dragEndPos = this->toPlaneCoords(mouseEvent->scenePos());
        QPointF translation = dragEndPos - this->dragStartPos;

        this->setPlane(
            this->plane.topLeft() - translation,
            this->plane.width(),
            this->plane.height()
            );

        this->dragStartPos = dragEndPos - translation;
    }

}

void GraphicScene::wheelEvent(QGraphicsSceneWheelEvent *wheelEvent)
{
    // std::cout<< "wheelEvent" << std::endl;
    double delta = wheelEvent->pixelDelta().y();
    QPointF cursorPos = wheelEvent->scenePos();
    // std::cout<< "cursor pos: " << cursorPos.x() << " " << cursorPos.y() << std::endl;
    double zoom = 1 - delta / this->graphicsWindow.width();
    if ((this->zoomPercent / zoom < 1) || (this->zoomPercent / zoom > 1000))
        return;
    double xRatio = (cursorPos.x() - this->graphicsWindow.left()) / this->graphicsWindow.width();
    double yRatio = (cursorPos.y() - this->graphicsWindow.top()) / this->graphicsWindow.height();
    // std::cout<< "ratios: " << xRatio << " " << yRatio << std::endl;
    QPointF newTopLeft = QPointF(
        cursorPos.x() - xRatio * zoom * this->graphicsWindow.width(),
        cursorPos.y() - yRatio * zoom * this->graphicsWindow.height()
        );
    QPointF newTopLeftPlane = this->toPlaneCoords(newTopLeft);
    // std::cout<< "new top left: " << newTopLeftPlane.x() << " " << newTopLeftPlane.y() << std::endl;
    this->setPlane(
        newTopLeftPlane,
        this->plane.width() * zoom, this->plane.height() * zoom
        );
    this->zoomPercent /= zoom;
    emit zoomChanged(this->zoomPercent);
}

void GraphicScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Qt::MouseButton buttonPressed = mouseEvent->button();
    if (buttonPressed == Qt::MouseButton::MiddleButton)
    {
        this->isDragged = false;
    }
}

void GraphicScene::removeIntersectingPoint(QPointF clickedPoint)
{
    // std::cout<< "removeIntersectingPoint" << std::endl;
    int index = -1;
    double minDistance = INFINITY;
    double pointSize = this->graphicsWindow.height() * 0.01 / this->cX;
    // // std::cout<< "Point size: " << pointSize << std::endl;
    for (size_t i = 0; i < this->points.size(); i++)
    {
        double curDistance = this->getDistance(this->points[i], clickedPoint);
        // // std::cout<< "Distance: " << curDistance << std::endl;
        if (curDistance < pointSize && curDistance < minDistance)
        {
            minDistance = curDistance;
            index = i;
        }
    }

    if (minDistance != INFINITY)
    {
        this->points.erase(this->points.begin() + index);
        this->update();
        emit pointsUpdated();
    }
}

double GraphicScene::getDistance(QPointF a, QPointF b)
{
    // std::cout<< "getDistance" << std::endl;
    return sqrt((a.x() - b.x()) * (a.x() - b.x()) + (a.y() - b.y()) * (a.y() - b.y()));
}

// points interactions

void GraphicScene::addPoint(QPointF point)
{
    // std::cout<< "addPoint" << std::endl;
    points.push_back(point);
    this->update();
    emit pointsUpdated();
}

std::vector<QPointF> GraphicScene::getPoints(void)
{
    // std::cout<< "getPoints" << std::endl;
    return points;
}

void GraphicScene::removeAllPoints(void)
{
    // std::cout<< "removeAllPoints" << std::endl;
    points.clear();
    emit pointsUpdated();
}

QStandardItemModel* GraphicScene::pointsModel(void)
{
    if (!pointsModel_)
        pointsModel_ = new QStandardItemModel(this);
    return pointsModel_;
}

void GraphicScene::updatePointsModel(void)
{
    auto model = pointsModel();
    model->clear();
    for (const auto& point : points) {
        auto item = new QStandardItem;
        item->setData(QVariant::fromValue(point), Qt::DisplayRole);
        auto index = model->index(model->rowCount(), 0);
        model->setData(index, point.x(), Qt::EditRole);
        model->setData(model->index(model->rowCount() - 1, 1), point.y(), Qt::EditRole);
        model->appendRow(item);
    }
}

void GraphicScene::zoomAtPercent(double zoom)
{
    QSizeF newSize = this->originalSize / (zoom / 100);
    QPointF oldSize = QPointF(this->plane.width(), this->plane.height());
    QPointF center = this->plane.topLeft() + (oldSize / 2);
    QPointF translate = QPointF(newSize.width() / 2, newSize.height() / 2);
    QPointF topLeft = center - translate;

    this->zoomPercent = zoom;
    this->setPlane(topLeft, newSize.width(), newSize.height());
}
