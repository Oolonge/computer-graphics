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
    ui->graphicsView->scale(1, -1); //coversion to normal coordinates

    ui->scaleInput->setText("100.00");
    // pointsTable
    ui->pointsView->setModel(scene->pointsModel());
    ui->pointsView->resizeColumnsToContents();
    ui->pointsView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->pointsView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->pointsView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->pointsView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->pointsView->verticalHeader()->setDefaultSectionSize(23);
    ui->pointsView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(scene, &GraphicScene::pointsUpdated, scene, &GraphicScene::updatePointsModel);

    connect(ui->showCoordinatesRadio, SIGNAL(toggled(bool)),
            this, SLOT(onShowCoordinatesRadioToggle(bool)));
    connect(ui->scaleInput, SIGNAL(editingFinished()),
            this, SLOT(onScaleInputEditFinished()));
    connect(scene, SIGNAL(zoomChanged(double)),
            this, SLOT(onZoomChanged(double)));
    connect(ui->solveButton, SIGNAL(clicked()),
            this, SLOT(OnSolveButtonClicked()));
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

void solutionpopup::onScaleInputEditFinished()
{
    this->scene->zoomAtPercent(ui->scaleInput->text().toDouble());
}

void solutionpopup::onZoomChanged(double value)
{
    ui->scaleInput->setText(QString::number(value));
}

void solutionpopup::OnSolveButtonClicked()
{
    int result = this->scene->solveProblem();
    this->scene->showSolution = !bool(result);
    if (result == 1)
        QMessageBox::warning(this, "warning", "Недостаточно точек для построения треугольника");
    else if (result == 2)
        QMessageBox::warning(this, "warning", "Все полученные треугольники вырожденные, невозможно решить задачу");
    else
        this->scene->update();
}


void solutionpopup::on_clearPlaneButton_clicked()
{
    this->scene->removeAllPoints();
}


void solutionpopup::on_toCetnerButton_clicked()
{
    this->scene->resetZoom();
    ui->scaleInput->setText("100.00");
}

