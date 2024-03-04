#ifndef SOLUTIONPOPUP_H
#define SOLUTIONPOPUP_H

#include <QDialog>
#include <QTableView>
#include <QMessageBox>
#include "graphicscene.h"


namespace Ui {
class solutionpopup;
}

class solutionpopup : public QDialog
{
    Q_OBJECT

public:
    explicit solutionpopup(QWidget *parent = nullptr);
    ~solutionpopup();
    GraphicScene *scene;

public slots:
    void onShowCoordinatesRadioToggle(bool checked);
    void onScaleInputEditFinished();
    void onZoomChanged(double value);
    void OnSolveButtonClicked();

private slots:
    void on_clearPlaneButton_clicked();
    void on_toCetnerButton_clicked();

private:
    Ui::solutionpopup *ui;
    QStandardItemModel *model;
    QTableView *pointsView;
};

#endif // SOLUTIONPOPUP_H
