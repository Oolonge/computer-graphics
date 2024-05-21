#include "figure.h"

int addPoint(const bool& cut_flag, const point& p, content& data)
{
    int rc = 0;
    if (cut_flag) {
        if (data.cut.close_flag) {
            data.cut.close_flag = false;
            data.cut.points.clear();
            data.cut.lines.clear();
        }
        data.cut.points.push_back(p);
        data.cut.update_lines(p);
    } else {
        size_t last_id = data.lines.size() - 1;
        if (data.lines[last_id].p1.is_null())
            data.lines[last_id].p1 = p;
        else {
            if (data.lines[last_id].p1 == p)
                rc = 2;
            else {
                data.lines[last_id].p2 = p;
                data.lines.push_back({});
            }
        }
    }
    return rc;
}

int vectorProduct(const point &vec1, const point &vec2)
{
    return vec1.x * vec2.y - vec1.y * vec2.x;
}

int sign(int num)
{
    if (num == 0)
        return 0;
    return (num >= 0) ? 1 : -1;
}

int checkConvex(const polygon &cut)
{
    size_t size = cut.points.size();
    if (size < 3)
        return false;

    point v1 = getVector(cut.lines[cut.lines.size() - 1]);
    point v2 = getVector(cut.lines[0]);

    int prev = sign(vectorProduct(v1, v2));

    for (size_t i = 0; i < cut.lines.size() - 1; i++)
    {
        v1 = getVector(cut.lines[i]);
        v2 = getVector(cut.lines[i + 1]);

        int cur = sign(vectorProduct(v1, v2));

        if (cur == 0 || prev == 0)
            continue;

        if (prev != cur)
            return 0;
        prev = cur;
    }

    return prev;
}


bool checkCross(const polygon &cut)
{

    for (size_t i = 0; i < cut.lines.size() - 1; i++)
    {
        point p1 = cut.lines[i].p1;
        point p2 = cut.lines[i].p2;
        for (size_t j = i + 1; j < cut.lines.size(); j++) {
            point p3 = cut.lines[j].p1;
            point p4 = cut.lines[j].p2;
            int v1 = vectorProduct(p3 - p4, p3 - p1);
            int v2 = vectorProduct(p3 - p4, p3 - p2);
            int v3 = vectorProduct(p1 - p2, p1 - p3);
            int v4 = vectorProduct(p1 - p2, p1 - p4);
            if ((v1 > 0) && (v2 < 0))
                return true;
            if ((v1 < 0) && (v2 > 0))
                return true;
            if ((v3 > 0) && (v4 < 0))
                return true;
            if ((v3 < 0) && (v4 > 0))
                return true;
        }
    }
    return false;
}

point getVector(line l)
{
    return {l.p2.x - l.p1.x, l.p2.y - l.p1.y};
}
