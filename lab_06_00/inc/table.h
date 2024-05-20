#ifndef TABLE_H
#define TABLE_H

#include "structures.h"
#include <QTableWidget>

int addPoint(const point &p, const colors col, const bool &hole_flag, QTableWidget *table, content &data);
void rewriteTable(const content &data, QTableWidget *table);
void addRow(const point &p, const int &n_figures, const int &n_holes, const size_t &i, QTableWidget *table);
void delRow(const indexes &ind_data, content &data);
int changePoint(const indexes &ind, const point &p, content &data);

#endif // TABLE_H
