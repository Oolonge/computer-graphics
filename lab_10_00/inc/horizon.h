#ifndef HORIZON_H
#define HORIZON_H

#include <QGraphicsView>
#include <QPointF>
#include <QLineF>
#include <QMatrix4x4>
#include <QVector3D>
#include <vector>
#include <functional>

namespace horizon {

struct Interval {
    double start, end, step;
    Interval(double s, double e, double st) : start(s), end(e), step(st) {}
};

struct Rotation {
    double angle_x, angle_y, angle_z;
    Rotation(double ax, double ay, double az) : angle_x(ax), angle_y(ay), angle_z(az) {}
};

struct Transformation {
    Rotation rotation;
    double scale_ratio;

    Transformation(Rotation r, double s) : rotation(r), scale_ratio(s) {}

    QVector3D rotate_vector(const QVector3D& vector) const;
    QVector3D scale_vector(const QVector3D& vector) const;
    QVector3D transform_vector(const QVector3D& vector) const;
};

class Horizon {
public:
    explicit Horizon(QGraphicsView* view);
    int visible(const QPointF& point) const;
    void update(const QLineF& line);
    QPointF top_intersection(const QPointF& point1, const QPointF& point2) const;
    QPointF bottom_intersection(const QPointF& point1, const QPointF& point2) const;

private:
    QGraphicsView* view;
    std::vector<int> top;
    std::vector<int> bottom;

    QPointF intersection(const QPointF& point1, const QPointF& point2, const std::vector<int>& horizon) const;
};

std::vector<QLineF> horizon_method(QGraphicsView* view, const Interval& x_interval, const Interval& z_interval,
                                   std::function<double(double, double)> func, const Transformation& transform);

} // namespace horizon

#endif // HORIZON_H
