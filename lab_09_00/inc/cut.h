#ifndef CUT_H
#define CUT_H

#include "structures.h"

bool findInter(point& p, line src, line sec, int norm);
bool isVisible(const line& src, const point& p, int norm);
void cut(content& data);

#endif // CUT_H
