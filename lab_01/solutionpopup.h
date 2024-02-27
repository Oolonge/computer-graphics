#ifndef SOLUTIONPOPUP_H
#define SOLUTIONPOPUP_H

#include <QDialog>
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
    void onSizeInputEditFinished();
    void onZoomChanged(double value);

private:
    Ui::solutionpopup *ui;
};

#endif // SOLUTIONPOPUP_H
