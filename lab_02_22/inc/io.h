#ifndef CONNECTION_H
#define CONNECTION_H
#include "volumetric_point.h"

struct connection
{
    int p1;
    int p2;
};

struct connections_data
{
    int n;
    connection *arr;
};

int read_amount(int* n, FILE* f);

int connections_alloc(connections_data &connections, int n);
void connections_free(connections_data &connections);
int read_connection(connection* joints, FILE* f);
int read_connections(connections_data &connections, int n, FILE *f);
int process_connections(connections_data& connections, FILE* f);

#endif // CONNECTION_H
