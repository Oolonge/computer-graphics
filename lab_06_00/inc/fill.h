#ifndef FILL_H
#define FILL_H

#include "structures.h"
#include <map>

bool comp(node a1, node a2); // artificial

void makeSleep(int sleep_time);
void drawCountor(const figure &f, QPainter &p);
int fillDelayed(const content &data, const int &delay, canvas_t &scene, gv_t &view, std::vector<double>& time);

#endif // FILL_H
