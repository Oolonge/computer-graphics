#include "solutionpopup.h"
#include "ui_solutionpopup.h"
#include "graphicscene.h"


solutionpopup::solutionpopup(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::solutionpopup)
{
    ui->setupUi(this);
    ui->showCoordinatesRadio->setChecked(true);

    // Scene
    scene = new GraphicScene(-5, -5, 10, 10, ui->showCoordinatesRadio->isChecked());
    ui->graphicsView->setScene(scene);

    connect(ui->showCoordinatesRadio, SIGNAL(toggled(bool)),
            this, SLOT(onShowCoordinatesRadioToggle(bool)));
    connect(ui->sizeInput, SIGNAL(editingFinished()),
            this, SLOT(onSizeInputEditFinished()));
    connect(scene, SIGNAL(zoomChanged(double)),
            this, SLOT(onZoomChanged(double)));
}

solutionpopup::~solutionpopup()
{
    delete scene;
    delete ui;
}

void solutionpopup::onShowCoordinatesRadioToggle(bool value)
{
    scene->setGridVisibility(value);
}

void solutionpopup::onSizeInputEditFinished()
{
    this->scene->zoomAtPercent(ui->sizeInput->text().toDouble());
}

void solutionpopup::onZoomChanged(double value)
{
    ui->sizeInput->setText(QString::number(value));
}
