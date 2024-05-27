#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing, false); //turn off built-in antialiasing
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->pushButtonCancel->setEnabled(false);

    data.backgroundColor = Qt::white;
    displayColor(data.backgroundColor, ui->label_bc);
    displayColor(line_color, ui->label_lc);

    ui->graphicsView->viewport()->installEventFilter(this);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag); //dragging
}

MainWindow::MainWindow(Test test, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->scale(1, -1); //coversion to normal coordinates
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing, false); //turn off built-in antialiasing
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->pushButtonCancel->setEnabled(false);

    data.backgroundColor = Qt::white;
    displayColor(data.backgroundColor, ui->label_bc);
    displayColor(line_color, ui->label_lc);

    ui->graphicsView->viewport()->installEventFilter(this);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag); //dragging

    if (!test.isEmpty())
    {
        this->populateTestData(test);
    }
}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
    cancel_stack = std::stack <objects_t>();
}

void MainWindow::populateTestData(Test test)
{
    if (!test.is_full())
        return;
    drawAxes();
    line_t line = test.line();
    drawLine(line, true, false);

    QRectF sceneRect = scene->sceneRect();
    QSize imageSize(sceneRect.size().toSize());
    QImage image(imageSize, QImage::Format_ARGB32);
    image.fill(Qt::white);

    QPainter painter(&image);
    scene->render(&painter);
    QString filename = QString("/Users/administrator/Desktop/qt/C++/lab_03_00/func_data/pics/%1.png").arg(test.name());
    image.save(filename, "png");

    this->deleteLater();
}


//overrides
void MainWindow::showEvent(QShowEvent *ev)
{
    QMainWindow::showEvent(ev);
    QTimer::singleShot(700, this, SLOT(drawAll()));
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    ui->graphicsView->resetTransform();
    drawAll();
}

void MainWindow::wheelEvent(QWheelEvent* event)
{
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    double scale_coeff = 1.05;
    if (event->angleDelta().y() > 0)
        ui->graphicsView->scale(scale_coeff, scale_coeff);
    else
        ui->graphicsView->scale(1 / scale_coeff, 1 / scale_coeff);
}

bool MainWindow::eventFilter(QObject* object, QEvent* event)
{
    if (event->type() == QEvent::Wheel && object == ui->graphicsView->viewport())
    {
        QWheelEvent *wheel_event = static_cast<QWheelEvent *>(event);
        wheelEvent(wheel_event);
        return true;
    }
    return false;
}

static void copy(struct objects_t **a, struct objects_t *b)
{
    for (size_t i = 0; i < b->lines.size(); i++)
        (*a)->lines.push_back(b->lines[i]);

    for (size_t i = 0; i < b->spectra.size(); i++)
        (*a)->spectra.push_back(b->spectra[i]);

    (*a)->backgroundColor = b->backgroundColor;
}

//output of errors and success after operations perfomance

void MainWindow::outputError(QString str)
{
    ui->textEdit->setTextColor(QColor(190, 20, 6)); // red
    ui->textEdit->setText(str);
    ui->textEdit->setTextColor(QColor(0, 0, 0)); // back to black
}


void MainWindow::outputSuccess(QString str)
{
    ui->textEdit->setTextColor(QColor(20, 130, 45)); // green
    ui->textEdit->setText(str);
    ui->textEdit->setTextColor(QColor(0, 0, 0)); // back to black
}


// drawing functions

// drawing parcer
void MainWindow::drawAll()
{
    scene->clear();
    ui->graphicsView->setBackgroundBrush(data.backgroundColor);
    drawAxes();

    for (size_t i = 0; i < data.spectra.size(); i++)
        drawSpectrum(data.spectra[i]);

    for (size_t i = 0; i < data.lines.size(); i++)
        drawLine(data.lines[i], true, false);
}

// drawing axes
void MainWindow::drawAxes()
{
    QPen pen = QPen(Qt::black, 2);
    // Oy
    scene->addLine(0, 0, 0, 400, pen);

    // Y-arrow
    scene->addLine(-6, 392, 0, 402, pen);
    scene->addLine(0, 402, 6, 392, pen);

    // Y
    scene->addLine(-6, 412, 0, 420, pen);
    scene->addLine(0, 420, 6, 412, pen);
    scene->addLine(0, 420, 0, 428, pen);

    // Ox
    scene->addLine(0, 0, 400, 0, pen);

    // X-arrow
    scene->addLine(400, 0, 392, 6, pen);
    scene->addLine(400, 0, 392, -6, pen);

    // X
    scene->addLine(410, -6, 418, 6, pen);
    scene->addLine(418, -6, 410, 6, pen);
}

int MainWindow::drawLine(line_t &line, bool drawingFlag, bool countStepsFlag)
{
    int steps_count = 0;
    switch (line.method)
    {
        case STANDART:
            standart_line(line, ui->graphicsView->scene());
            break;
        case DDA:
            steps_count = dda_line(line, ui->graphicsView->scene(), drawingFlag, countStepsFlag);
            break;
        case BRESEN_INT:
            steps_count = bresen_int_line(line, ui->graphicsView->scene(), drawingFlag, countStepsFlag);
            break;
        case BRESEN_DOUBLE:
            steps_count = bresen_double_line(line, ui->graphicsView->scene(), drawingFlag, countStepsFlag);
            break;
        case BRESEN_STEPS:
            steps_count = bresen_steps_line(line, ui->graphicsView->scene(), drawingFlag, countStepsFlag);
            break;
        case WY:
            steps_count = wy_line(line, ui->graphicsView->scene(), drawingFlag, countStepsFlag);
            break;
    }
    if (countStepsFlag)
        return steps_count;
    return -1;
}

void MainWindow::drawSpectrum(spectre_t &spectrum)
{
    double x, y;
    QPointF currentEndPoint;
    line_t line;
    line.color = spectrum.color;
    line.method = spectrum.method;
    line.start = spectrum.center;
    for (int i = 0; i <= 360; i += spectrum.angle)
    {
        y = spectrum.center.y() + sin(M_PI * i / 180) * spectrum.radius;
        x = spectrum.center.x() + cos(M_PI * i / 180) * spectrum.radius;
        currentEndPoint = QPointF(x, y);
        line.end = currentEndPoint;
        drawLine(line, true, false);
    }
}

// показать цвет на лейбл
void MainWindow::displayColor(QColor color, QLabel *lab)
{
    QImage im = QImage(lab->geometry().width(), lab->geometry().height(), QImage::Format_RGB32);
    QPainter p(&im);
    p.setBrush(QBrush(color));
    p.setPen(Qt::black);
    QRect rect = QRect(0, 0, lab->geometry().width(), lab->geometry().height());
    p.drawRect(rect);

    QPixmap pixmap = QPixmap::fromImage(im);
    lab->clear();
    lab->setPixmap(pixmap);
}

void MainWindow::setBackroundColor()
{
    QColorDialog colorDialog;
    colorDialog.setCurrentColor(data.backgroundColor);
    colorDialog.show();
    colorDialog.exec();

    QColor selectedColor = colorDialog.selectedColor();
    if (!selectedColor.isValid())
        outputError("Color setting error");
    else
        backgroundColor = selectedColor;
    displayColor(backgroundColor, ui->label_bc);
}


void MainWindow::setLineColor()
{
    QColorDialog dialog;
    dialog.setCurrentColor(line_color);
    dialog.show();
    dialog.exec();
    QColor color = dialog.selectedColor();
    if (!color.isValid())
        outputError("Color setting error");
    else
        line_color = color;
    displayColor(line_color, ui->label_lc);
}


void MainWindow::readLineData()
{
    QString x_start_str = ui->lineEdit_line_x_start->text();
    QString y_end_str = ui->lineEdit_line_y_end->text();

    QString y_start_str = ui->lineEdit_line_y_start->text();
    QString x_end_str = ui->lineEdit_line_x_end->text();

    if (x_end_str.length() == 0 || x_start_str.length() == 0 || y_end_str.length() == 0 || y_start_str.length() == 0)
    {
        outputError("Input error!");
        return;
    }

    bool x_start_flag, y_start_flag, x_end_flag, y_end_flag;
    double x_start_double, y_start_double, x_end_double, y_end_double;
    x_start_double = x_start_str.toDouble(&x_start_flag);
    y_start_double = y_start_str.toDouble(&y_start_flag);
    x_end_double = x_end_str.toDouble(&x_end_flag);
    y_end_double = y_end_str.toDouble(&y_end_flag);

    if (!x_start_flag || !x_end_flag || !y_start_flag || !y_end_flag)
    {
        outputError("Input erorr: incorrect input");
        return;
    }

    QPointF start_point, end_point;
    start_point = QPointF(x_start_double, y_start_double);
    end_point = QPointF(x_end_double, y_end_double);

    if (start_point == end_point)
    {
        outputError("Error! Points of the begging and the end match");
        return;
    }

    objects_t *c = new objects_t;
    copy(&c, &data);
    cancel_stack.push(*c);
    ui->pushButtonCancel->setEnabled(true);

    line_t line;
    line.color = line_color;
    line.method = (method_t) ui->comboBox->currentIndex();
    line.start = start_point;
    line.end = end_point;
    data.lines.push_back(line);
    drawLine(line, true, false);
    ui->graphicsView->setBackgroundBrush(backgroundColor);
    data.backgroundColor = backgroundColor;
    outputSuccess("Success");
}


void MainWindow::readSpectrumData()
{
    QString spectrum_x_str = ui->lineEdit_spectrum_x->text();
    QString spectrum_y_str = ui->lineEdit_spectrum_y->text();
    QString spectrum_r_str = ui->lineEdit_spectrum_radius->text();
    QString angle_Str = ui->lineEdit_angle->text();

    if (spectrum_x_str.length() == 0 || spectrum_y_str.length() == 0 || spectrum_r_str.length() == 0 || angle_Str.length() == 0)
    {
        outputError("Input error!");
        return;
    }

    bool spectrum_x_flag, spectrum_y_flag, spectrum_r_flag, angle_flag;
    double spectrum_x_double, spectrum_y_double;
    double spectrum_r_double, angle_double;

    spectrum_x_double = spectrum_x_str.toDouble(&spectrum_x_flag);
    spectrum_y_double = spectrum_y_str.toDouble(&spectrum_y_flag);
    spectrum_r_double = spectrum_r_str.toDouble(&spectrum_r_flag);
    angle_double = angle_Str.toDouble(&angle_flag);

    if (!spectrum_x_flag || !spectrum_y_flag || !spectrum_r_flag || !angle_flag)
    {
        outputError("Input error: incorrect input");
        return;
    }

    objects_t *c = new objects_t;
    copy(&c, &data);
    cancel_stack.push(*c);
    ui->pushButtonCancel->setEnabled(true);

    QPointF center = QPointF(spectrum_x_double, spectrum_y_double);

    spectre_t spectre;
    spectre.center = center;
    spectre.angle = angle_double;
    spectre.color = line_color;
    spectre.method = (method_t) ui->comboBox->currentIndex();
    spectre.radius = spectrum_r_double;
    data.spectra.push_back(spectre);
    data.backgroundColor = backgroundColor;
    ui->graphicsView->setBackgroundBrush(backgroundColor);
    drawSpectrum(spectre);
    outputSuccess("Success");
}


void MainWindow::clearCanvas()
{
    data.backgroundColor = Qt::white;
    backgroundColor = Qt::white;
    line_color = Qt::black;
    displayColor(data.backgroundColor, ui->label_bc);
    displayColor(line_color, ui->label_lc);
    data.lines.clear();
    data.spectra.clear();
    cancel_stack = std::stack<objects_t>();
    outputSuccess("Clear successful");
    ui->graphicsView->resetTransform();
    drawAll();
    ui->pushButtonCancel->setEnabled(false);
}

void MainWindow::cancelAction()
{
    if (!cancel_stack.empty())
    {
        data = cancel_stack.top();
        cancel_stack.pop();
        drawAll();
    }
    if (cancel_stack.empty())
        ui->pushButtonCancel->setEnabled(false);
}
