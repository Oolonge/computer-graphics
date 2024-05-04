#include "../inc/graphicscene.h"

GraphicScene::GraphicScene(double x, double y, double w, double h,
                           bool isVisible, QObject *parent)
    : QGraphicsScene{parent} {
  this->setGridVisibility(isVisible);
  this->setPlane(x, y, w, h, false);
  this->setGraphicsWindow(x, y, w, h, false);
  this->originalSize = QSizeF(w, h);
  this->zoomPercent = 100;
}

double GraphicScene::getCX(void) { return this->cX; }

double GraphicScene::getCY(void) { return this->cY; }

void GraphicScene::setCX(double c) { this->cX = c; }

void GraphicScene::setCY(double c) { this->cY = c; }

bool GraphicScene::gridIsVisible(void) { return gridVisible; }

void GraphicScene::setGridVisibility(bool value) {
  gridVisible = value;
  this->update();
}

void GraphicScene::setPlane(QRectF rect, bool update) {
  this->plane = rect;
  this->computeCoefficients();

  if (update) {
    this->update();
  }
}

void GraphicScene::setPlane(double x, double y, double w, double h,
                            bool update) {
  this->plane = QRectF(x, y, w, h);
  this->computeCoefficients();

  if (update)
    this->update();
}

void GraphicScene::setPlane(QPointF topLeft, double w, double h, bool update) {
  this->plane = QRectF(topLeft.x(), topLeft.y(), w, h);
  this->computeCoefficients();

  if (update)
    this->update();
}

QRectF GraphicScene::getPlane(void) { return this->plane; }

void GraphicScene::setGraphicsWindow(double x, double y, double w, double h,
                                     bool update) {
  this->graphicsWindow = QRectF(x, y, w, h);
  this->originalGraphicsWindow = QRectF(x, y, w, h);
  this->computeCoefficients();

  if (update)
    this->update();
}

void GraphicScene::setGraphicsWindow(QRectF rect) {
  this->graphicsWindow = rect;
  this->computeCoefficients();
}

QRectF GraphicScene::getGraphicsWindow(void) { return this->graphicsWindow; }

void GraphicScene::computeCoefficients(void) {
  if (!this->plane.isValid() || !this->graphicsWindow.isValid()) {
    return;
  }

  this->setCX(this->graphicsWindow.width() / this->plane.width());
  this->setCY(this->graphicsWindow.height() / this->plane.height());
}

QPointF GraphicScene::toPlaneCoords(QPointF windowCoords) {
  QPointF planeCoords = windowCoords;

  if (this->cX == 0 || this->cY == 0) {
    throw std::runtime_error(
        "Коэффициент равен нулю. Невозможно совершить преобразование"); // new?
  }

  planeCoords.setX((windowCoords.x() - this->graphicsWindow.topLeft().x()) /
                       this->cX +
                   this->plane.topLeft().x());
  planeCoords.setY((windowCoords.y() - this->graphicsWindow.topLeft().y()) /
                       this->cY +
                   this->plane.topLeft().y());

  return planeCoords;
}

QPointF GraphicScene::toWindowCoords(QPointF planeCoords) {
  QPointF windowCoords = planeCoords;

  windowCoords.setX((planeCoords.x() - this->plane.topLeft().x()) * this->cX +
                    this->graphicsWindow.topLeft().x());
  windowCoords.setY((planeCoords.y() - this->plane.topLeft().y()) * this->cY +
                    this->graphicsWindow.topLeft().y());

  return windowCoords;
}

void GraphicScene::drawForeground(QPainter *painter, const QRectF &rect) {
  this->setGraphicsWindow(rect);
  painter->setPen(Qt::blue);
  painter->setBrush(Qt::blue);
  for (auto point : this->points) {
    this->drawPoint(painter, point, 0.008);
  }
  if (showSolution)
    this->drawPointConnections(painter, res_triangle);
}

void GraphicScene::drawBackground(QPainter *painter, const QRectF &rect) {
  // graphics update
  this->setGraphicsWindow(rect);

  // background colour to white
  painter->fillRect(this->getGraphicsWindow(), Qt::white);

  // lines and center
  painter->setPen(Qt::black);
  bool intersectsX = this->plane.top() <= 0 && this->plane.bottom() >= 0;
  bool intersectsY = this->plane.left() <= 0 && this->plane.right() >= 0;

  if (intersectsX) {
    this->drawXAxis(painter);
  }
  if (intersectsY) {
    this->drawYAxis(painter);
  }
  if (intersectsX && intersectsY) {
    this->drawCenter(painter);
  }
  if (!this->gridIsVisible()) {
    return;
  }

  painter->setPen(Qt::gray);
  painter->setBrush(Qt::gray);
  // draw grid
  for (long x = this->plane.left() - 1; x < this->plane.right() + 1; x++) {
    QPointF top = this->toWindowCoords(QPointF(x, this->plane.top()));
    QPointF bottom = this->toWindowCoords(QPointF(x, this->plane.bottom()));
    painter->drawLine(top, bottom);
  }

  for (long y = this->plane.top() - 1; y < this->plane.bottom() + 1; y++) {
    QPointF left = this->toWindowCoords(QPointF(this->plane.left(), y));
    QPointF right = this->toWindowCoords(QPointF(this->plane.right(), y));
    painter->drawLine(left, right);
  }

  // so that it would stay
  painter->setPen(Qt::black);
  if (intersectsX) {
    this->drawXAxis(painter);
  }
  if (intersectsY) {
    this->drawYAxis(painter);
  }
  if (intersectsX && intersectsY) {
    this->drawCenter(painter);
  }
}

void GraphicScene::drawXAxis(QPainter *painter) {
  painter->setPen(Qt::black);
  QPointF xAxisStart = this->toWindowCoords(QPointF(this->plane.left(), 0));
  QPointF xAxisEnd = this->toWindowCoords(QPointF(this->plane.right(), 0));
  painter->drawLine(xAxisStart, xAxisEnd);
}

void GraphicScene::drawYAxis(QPainter *painter) {
  painter->setPen(Qt::black);
  QPointF yAxisStart = this->toWindowCoords(QPointF(0, this->plane.top()));
  QPointF yAxisEnd = this->toWindowCoords(QPointF(0, this->plane.bottom()));
  painter->drawLine(yAxisStart, yAxisEnd);
}

void GraphicScene::drawCenter(QPainter *painter) {
  painter->setPen(Qt::red);
  painter->setBrush(Qt::red);
  QPointF center = QPointF(0, 0);

  this->drawPoint(painter, center, 0.005);
}

/**
 * @brief Draws a point on coordinate plane
 * @param painter doesn't change pen/brush color itself
 * @param point plane coordinates
 * @param k size coefficient
 */
void GraphicScene::drawPoint(QPainter *painter, QPointF point, double k) {
  QPointF convertedPoint = this->toWindowCoords(point);
  double rx = this->graphicsWindow.width() * k;
  double ry = this->graphicsWindow.height() * k;
  painter->drawEllipse(convertedPoint, rx, ry);
}

void GraphicScene::drawPointConnections(QPainter *painter,
                                        QVector<QPointF> pointsToConnect) {
  auto arr_size = pointsToConnect.size();
  if (arr_size < 3)
    return;
  for (auto i = 0; i < arr_size; i++) {
    QPointF convertedPoint1 =
        this->toWindowCoords(pointsToConnect[i % arr_size]);
    QPointF convertedPoint2 =
        this->toWindowCoords(pointsToConnect[(i + 1) % arr_size]);
    painter->drawLine(convertedPoint1, convertedPoint2);
    if (i == bisectorFrom) {
      QPointF convertedTop = this->toWindowCoords(pointsToConnect[i]);
      QPointF convertedBisec = this->toWindowCoords(bisectorPoint);
      painter->drawLine(convertedTop, convertedBisec);
    }
  }
}

void GraphicScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  QPointF windowPoint = mouseEvent->scenePos();
  Qt::MouseButton buttonPressed = mouseEvent->button();
  if (buttonPressed == Qt::MouseButton::LeftButton) {
    this->addPoint(this->toPlaneCoords(windowPoint));
  } else if (buttonPressed == Qt::MouseButton::MiddleButton) {
    if (!this->isDragged) {
      this->dragStartPos = this->toPlaneCoords(windowPoint);
      this->isDragged = true;
    }
  } else if (buttonPressed == Qt::MouseButton::RightButton) {
    this->removeIntersectingPoint(this->toPlaneCoords(windowPoint));
  }
}

void GraphicScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  if (mouseEvent->buttons() & Qt::MouseButton::MiddleButton) {
    QPointF dragEndPos = this->toPlaneCoords(mouseEvent->scenePos());
    QPointF translation = dragEndPos - this->dragStartPos;

    this->setPlane(this->plane.topLeft() - translation, this->plane.width(),
                   this->plane.height());

    this->dragStartPos = dragEndPos - translation;
  }
}

void GraphicScene::wheelEvent(QGraphicsSceneWheelEvent *wheelEvent) {
  double delta = wheelEvent->pixelDelta().y();
  QPointF cursorPos = wheelEvent->scenePos();

  double zoom = 1 - delta / this->graphicsWindow.width();
  if ((this->zoomPercent / zoom < MIN_ZOOM_PERCENT) ||
      (this->zoomPercent / zoom > MAX_ZOOM_PERCENT))
    return;

  double xRatio = (cursorPos.x() - this->graphicsWindow.left()) /
                  this->graphicsWindow.width();
  double yRatio = (cursorPos.y() - this->graphicsWindow.top()) /
                  this->graphicsWindow.height();

  QPointF newTopLeft =
      QPointF(cursorPos.x() - xRatio * zoom * this->graphicsWindow.width(),
              cursorPos.y() - yRatio * zoom * this->graphicsWindow.height());
  QPointF newTopLeftPlane = this->toPlaneCoords(newTopLeft);

  this->setPlane(newTopLeftPlane, this->plane.width() * zoom,
                 this->plane.height() * zoom);

  this->zoomPercent /= zoom;
  emit zoomChanged(this->zoomPercent);
}

void GraphicScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  Qt::MouseButton buttonPressed = mouseEvent->button();
  if (buttonPressed == Qt::MouseButton::MiddleButton)
    this->isDragged = false;
}

void GraphicScene::removeIntersectingPoint(QPointF clickedPoint) {
  int index = -1;
  double minDistance = INFINITY;
  double pointSize = this->graphicsWindow.height() * 0.01 / this->cX;

  for (qsizetype i = 0; i < this->points.size(); i++) {
    double currentDistance = this->getDistance(this->points[i], clickedPoint);

    if (currentDistance < pointSize && currentDistance < minDistance) {
      minDistance = currentDistance;
      index = i;
    }
  }

  if (minDistance != INFINITY) {
    this->points.erase(this->points.begin() + index);
    this->update();
    emit pointsUpdated();
  }
}

double GraphicScene::getDistance(QPointF a, QPointF b) {
  return sqrt((a.x() - b.x()) * (a.x() - b.x()) +
              (a.y() - b.y()) * (a.y() - b.y()));
}

void GraphicScene::addPoint(QPointF point) {
  if (isDuplicate(points, point) == false) {
    points.push_back(point);
    this->update();
    emit pointsUpdated();
  }
}

QVector<QPointF> GraphicScene::getPoints(void) { return points; }

void GraphicScene::removeAllPoints(void) {
  points.clear();
  showSolution = false;
  this->update();
  emit pointsUpdated();
}

QStandardItemModel *GraphicScene::pointsModel(void) {
  if (!pointsModel_)
    pointsModel_ = new QStandardItemModel(points.size(), 2, this);

  return pointsModel_;
}

void GraphicScene::updatePointsModel(void) {
  auto model = pointsModel(); // QStandardItemModel
  model->clear();
  model->setHorizontalHeaderLabels(QStringList() << "X"
                                                 << "Y");

  for (const auto &point : points) {
    QList<QStandardItem *> items;
    QStandardItem *item_x = new QStandardItem(), *item_y = new QStandardItem();
    item_x->setData(QVariant(point.x()), Qt::DisplayRole);
    item_y->setData(QVariant(point.y()), Qt::DisplayRole);
    items.append(item_x);
    items.append(item_y);
    model->appendRow(items);
  }
}

void GraphicScene::zoomAtPercent(double zoom) {
  QSizeF newSize = this->originalSize / (zoom / 100);
  QPointF oldSize = QPointF(this->plane.width(), this->plane.height());
  QPointF center = this->plane.topLeft() + (oldSize / 2);
  QPointF translate = QPointF(newSize.width() / 2, newSize.height() / 2);
  QPointF topLeft = center - translate;

  this->zoomPercent = zoom;
  this->setPlane(topLeft, newSize.width(), newSize.height());
}

bool GraphicScene::isDuplicate(QVector<QPointF> points, QPointF point) {
  for (int i = 0; i < points.size(); i++) {
    if (points[i].x() == point.x() && points[i].y() == point.y())
      return true;
  }
  return false;
}

void GraphicScene::resetZoom(void) {
  this->setGraphicsWindow(this->originalGraphicsWindow);
  this->setPlane(this->originalGraphicsWindow);
  this->zoomPercent = 100;
}
