#include "requests.h"
#include "table.h"
#include "drawing.h"
#include "fill.h"
#include <map>

void cancelData(const content &data, QTableWidget *table, canvas_t &scene, gv_t &view)
{
    rewriteTable(data, table);
    drawPoints(scene, view, false, {0, 0}, data);
}

void deletePoint(const indexes &ind_data, content &data, QTableWidget *table, canvas_t &scene, gv_t &view)
{
    delRow(ind_data, data);
    rewriteTable(data, table);
    drawPoints(scene, view, false, {0, 0}, data);
}

int change(const indexes &ind, const point &p, content &data, QTableWidget *table, canvas_t &scene, gv_t &view)
{
    int rc = changePoint(ind, p, data);
    if (!rc)
    {
        rewriteTable(data, table);
        drawPoints(scene, view, true, p, data);
    }
    return rc;
}

void fillAll(content &data, const int delay, canvas_t &scene, gv_t &view, std::vector<double>& time)
{
    for (size_t i = 0; i < data.figures.size(); i++)
        fillSingle(data.figures[i], delay, scene, view, time);
}

int handle_request(request &req)
{
    int rc = 0;
    switch (req.oper)
    {
        case DRAW:
            drawPoints(req.scene, req.view, req.hole_figure_flag, req.p, req.data);
            break;
        case FILL_AREA:
            fillAll(req.data, req.delay, req.scene, req.view, req.time);
            break;
        case ADD_POINT:
            rc = addPoint(req.p, req.colors_data, req.hole_figure_flag, req.table, req.data);
            break;
        case DELETE_POINT:
            deletePoint(req.indexes_data, req.data, req.table, req.scene, req.view);
            break;
        case CANCEL_ACTION:
            cancelData(req.data, req.table, req.scene, req.view);
            break;
        case CHANGE_POINT:
            rc = change(req.indexes_data, req.p, req.data, req.table, req.scene, req.view);
            break;
        case SELECT_POINT:
            selectPoint(req.scene, req.view, req.p, req.data);
            break;
    }
    return rc;
}
