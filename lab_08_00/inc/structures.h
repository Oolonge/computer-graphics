#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <QGraphicsScene>
#include <QGraphicsView>

typedef QGraphicsScene* canvas_t;
typedef QGraphicsView* gv_t;

struct point {
    int x = 0;
    int y = 0;

    bool is_null() { return !(x > 0 && y > 0); };
    bool is_null() const { return !(x > 0 && y > 0); };
    bool operator==(const point& p) { return x == p.x && y == p.y; };
    bool operator!=(const point& p) { return !operator==(p); };
    point operator-(const point& p) const { return { x - p.x, y - p.y }; };
    point operator+(const point &p) const {return {x + p.x, y + p.y}; };
    point operator*(const int &num) { return {x * num, y * num}; };
};

struct line {
    point p1;
    point p2;

    bool is_full() { return !(p1.is_null() || p2.is_null()); };
    bool is_full() const { return !(p1.is_null() || p2.is_null()); };
};

struct polygon {
    std::vector<point> points;
    std::vector<line> lines = {};
    bool close_flag;

    void update_lines(const point &p)
    {
        if (lines.empty()) {
            lines.push_back({});
            lines[0].p1 = p;
        } else {
            size_t last = lines.size() - 1;
            lines[last].p2 = p;
            if (!close_flag) {
                lines.push_back({});
                lines[++last].p1 = p;
            }
        }
    }
};

struct content {
    polygon cut;
    std::vector<line> lines;
    std::vector<line> visible_lines;
    QColor line_color;
    QColor visible_color;
    QColor cut_color;
};

#endif // STRUCTURES_H
