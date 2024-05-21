#ifndef CUT_H
#define CUT_H

#include "structures.h"

int scalarProduct(point p1, point p2);
bool cutLine(line& res_line, const line& src, const polygon& cut);
void cut(content& data);

#endif // CUT_H
