#ifndef TABLE_H
#define TABLE_H

#include "structures.h"
#include <QTableWidget>

int addPoint(const point &p, const colors col, const bool &is_hole, QTableWidget *table, content &data);
void rewriteTable(const content &data, QTableWidget *table);
void delRow(const indexes &ind_data, content &data);
int changePoint(const indexes &ind, const point &p, content &data);

#endif // TABLE_H
