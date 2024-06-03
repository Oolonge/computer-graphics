#include "horizon.h"
#include <QGraphicsView>
#include <QPointF>
#include <QLineF>
#include <QMatrix4x4>
#include <QVector3D>
#include <vector>
#include <functional>

namespace horizon {

constexpr int TOP = 1;
constexpr int BOTTOM = -1;
constexpr int INVISIBLE = 0;

QVector3D Transformation::rotate_vector(const QVector3D& vector) const {
    QMatrix4x4 transform;
    transform.rotate(rotation.angle_x, 1, 0, 0);
    transform.rotate(rotation.angle_y, 0, 1, 0);
    transform.rotate(rotation.angle_z, 0, 0, 1);
    return transform.map(vector);
}

QVector3D Transformation::scale_vector(const QVector3D& vector) const {
    QMatrix4x4 transform;
    transform.scale(scale_ratio);
    return transform.map(vector);
}

QVector3D Transformation::transform_vector(const QVector3D& vector) const {
    return scale_vector(rotate_vector(vector));
}

Horizon::Horizon(QGraphicsView* view) : view(view), top(view->width(), 0), bottom(view->width(), view->height()) {}

int Horizon::visible(const QPointF& point) const {
    QPoint p = view->mapFromScene(point);
    if (p.y() <= bottom[p.x()]) {
        return BOTTOM;
    } else if (p.y() >= top[p.x()]) {
        return TOP;
    }
    return INVISIBLE;
}

void Horizon::update(const QLineF& line) {
    QPoint p1 = view->mapFromScene(line.p1());
    QPoint p2 = view->mapFromScene(line.p2());
    int x1 = p1.x(), y1 = p1.y(), x2 = p2.x(), y2 = p2.y();

    if (x2 - x1 == 0) {
        top[x2] = std::max(top[x2], y2);
        bottom[x2] = std::min(bottom[x2], y2);
        return;
    }

    double m = static_cast<double>(y2 - y1) / (x2 - x1);
    for (int x = x1; x <= x2; ++x) {
        int y = std::round(m * (x - x1) + y1);
        top[x] = std::max(top[x], y);
        bottom[x] = std::min(bottom[x], y);
    }
}

QPointF Horizon::intersection(const QPointF& point1, const QPointF& point2, const std::vector<int>& horizon) const {
    QPoint p1 = view->mapFromScene(point1);
    QPoint p2 = view->mapFromScene(point2);
    int x1 = p1.x(), y1 = p1.y(), x2 = p2.x(), y2 = p2.y();
    int dx = x2 - x1;
    int dyc = y2 - y1;
    int dyp = horizon[x2] - horizon[x1];

    if (dx == 0) {
        return view->mapToScene(QPoint(x2, horizon[x2]));
    }

    if (y1 == horizon[x1] && y2 == horizon[x2]) {
        return view->mapToScene(QPoint(x1, y1));
    }

    double m = static_cast<double>(dyc) / dx;
    int xi = x1 - std::round(dx * (y1 - horizon[x1]) / (dyc - dyp));
    int yi = std::round((xi - x1) * m + y1);
    return view->mapToScene(QPoint(xi, yi));
}

QPointF Horizon::top_intersection(const QPointF& point1, const QPointF& point2) const {
    return intersection(point1, point2, top);
}

QPointF Horizon::bottom_intersection(const QPointF& point1, const QPointF& point2) const {
    return intersection(point1, point2, bottom);
}

std::vector<QLineF> horizon_method(QGraphicsView* view, const Interval& x_interval, const Interval& z_interval,
                                   std::function<double(double, double)> func, const Transformation& transform) {
    std::vector<QLineF> result_lines;
    Horizon horizon(view);
    QPointF left, right;

    for (double z = z_interval.end; z >= z_interval.start - z_interval.step / 2; z -= z_interval.step) {
        QVector3D prev_vec(x_interval.start, func(x_interval.start, z), z);
        QPointF prev = transform.transform_vector(prev_vec).toPointF();
        int flag_prev = horizon.visible(prev);

        if (!left.isNull()) {
            result_lines.emplace_back(left, prev);
            horizon.update(QLineF(left, prev));
        }
        left = prev;

        for (double x = x_interval.start; x <= x_interval.end + x_interval.step / 2; x += x_interval.step) {
            QVector3D curr_vec(x, func(x, z), z);
            QPointF curr = transform.transform_vector(curr_vec).toPointF();
            int flag_curr = horizon.visible(curr);

            if (flag_prev != flag_curr) {
                if (flag_prev == TOP || flag_curr == TOP) {
                    QPointF top_intersection = horizon.top_intersection(prev, curr);
                    result_lines.emplace_back(flag_prev == TOP ? prev : curr, top_intersection);
                }
                if (flag_prev == BOTTOM || flag_curr == BOTTOM) {
                    QPointF bottom_intersection = horizon.bottom_intersection(prev, curr);
                    result_lines.emplace_back(flag_prev == BOTTOM ? prev : curr, bottom_intersection);
                }
            } else if (flag_curr != INVISIBLE) {
                result_lines.emplace_back(prev, curr);
                horizon.update(QLineF(prev, curr));
            }

            prev = curr;
            flag_prev = flag_curr;
        }

        if (!right.isNull()) {
            result_lines.emplace_back(prev, right);
            horizon.update(QLineF(prev, right));
        }
        right = prev;
    }

    return result_lines;
}

} // namespace horizon
