#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <QGraphicsScene>
#include <QGraphicsView>

typedef QGraphicsScene* canvas_t;
typedef QGraphicsView* gv_t;

class point {
public:
    int x = -1;
    int y = -1;

    point operator-(const point& p) const { return { x - p.x, y - p.y }; }
    bool operator==(const point& p) { return x == p.x && y == p.y; }
    bool operator!=(const point& p) { return !operator==(p); }
    bool is_null() { return !(x > 0 && y > 0); }
    bool is_null() const { return !(x > 0 && y > 0); }
};

class figure {
public:
    point p1;
    point p2;

    bool is_full() const { return !(p1.is_null() || p2.is_null()); }
    bool is_full() { return !(p1.is_null() || p2.is_null()); }
};

struct content {
    std::vector<figure> lines;
    std::vector<figure> visible_lines;
    figure cut;
    QColor line_color;
    QColor visible_color;
    QColor cut_color;
    int cut_amount = 0;
};

#endif // STRUCTURES_H
