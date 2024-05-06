#ifndef FILL_H
#define FILL_H

#include "structures.h"
#include <map>

std::map<int, std::vector<node>> makeYgroup(const figure& fig, int& y_max, int& y_min);

bool comp(node a1, node a2);

void updateYgroup(point p_start, point p_end, std::map<int, std::vector<node>>& y_group, int& y_max, int& y_min);
void checkActiveEdges(std::vector<node>& active_edges);
void addActiveEdges(std::map<int, std::vector<node>>& y_group, std::vector<node>& active_edges, int y);
void makeSleep(int sleep_time);
void drawFastStr(QPainter& p, std::vector<node>& active_edges, int& y);
void drawStr(gv_t& view, canvas_t& scene, std::vector<node>& active_edges, int& y, QColor color);
void drawConnections(const figure& f, canvas_t& scene, gv_t& view);
void fillSingle(const figure& f, const int& delay, canvas_t& scene, gv_t& view, std::vector<double>& time);

#endif // FILL_H
