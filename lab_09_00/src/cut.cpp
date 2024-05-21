#include "cut.h"
#include "figure.h"
#include <cmath>

bool isVisible(const line& src, const point& p, int norm)
{
    point v1 = src.p2 - src.p1;
    point v2 = p - src.p2;

    int pr = vectorProduct(v1, v2);

    if (pr * norm >= 0)
        return true;

    return false;
}

bool findInter(point& p, line src, line sec, int norm)
{
    bool vis1 = isVisible(src, sec.p1, norm);
    bool vis2 = isVisible(src, sec.p2, norm);
    bool inter_flag = (vis1 || vis2) && (!(vis1 && vis2));

    if (inter_flag) {
        point cut_vec = src.p2 - src.p1;
        point pol_vec = sec.p2 - sec.p1;

        long nominator = cut_vec.y * (sec.p1.x - src.p1.x) - cut_vec.x * (sec.p1.y - src.p1.y);
        long denomanator = pol_vec.y * cut_vec.x - pol_vec.x * cut_vec.y;

        if (denomanator == 0)
            p = sec.p2;
        else {
            double t = (double)nominator / denomanator;
            point tmp = sec.p2 - sec.p1;
            tmp = { int(tmp.x * t), int(tmp.y * t) };
            p = sec.p1 + tmp;
        }
    }

    return inter_flag;
}

void cut(content& data)
{
    int normal = checkConvex(data.cutter);
    data.visible_figure = data.figure;
    for (auto cut_line : data.cutter.lines) {
        polygon new_pol;
        for (auto vis_line : data.visible_figure.lines) {
            point inter;

            bool inter_flag = findInter(inter, cut_line, vis_line, normal);
            if (inter_flag) {
                new_pol.points.push_back(inter);
                if (new_pol.points.size() > 1)
                    new_pol.lines.push_back({ new_pol.points[new_pol.points.size() - 2],
                        new_pol.points[new_pol.points.size() - 1] });
            }

            bool is_vis = isVisible(cut_line, vis_line.p2, normal);
            if (is_vis) {
                new_pol.points.push_back(vis_line.p2);
                if (new_pol.points.size() > 1)
                    new_pol.lines.push_back({ new_pol.points[new_pol.points.size() - 2],
                        new_pol.points[new_pol.points.size() - 1] });
            }
        }
        new_pol.is_close = false;
        if (new_pol.points.size() > 2) {
            new_pol.is_close = true;
            new_pol.lines.push_back({ new_pol.points[new_pol.points.size() - 1],
                                 new_pol.points[0] });
        }
        data.visible_figure = new_pol;
    }
}
