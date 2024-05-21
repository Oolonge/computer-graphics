#ifndef FIGURE_H
#define FIGURE_H

#include "structures.h"

int addPoint(const bool& cut_flag, const point& p, content& data);

int vectorProduct(const point &v1, const point &v2);
int sign(int num);
int checkConvex(const polygon &cut);

bool checkCross(const polygon &cut);
point getVector(line l);

#endif // FIGURE_H
