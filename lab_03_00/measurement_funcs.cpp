#include "mainwindow.h"

void MainWindow::MeasureSteps(spectre_t spectrum, std::vector<int> &all_steps)
{
    double x, y;
    QPointF cur_end;
    line_t line;
    line.color = spectrum.color;
    line.method = spectrum.method;
    line.start = spectrum.center;
    int step;
    for (double j = 0.0; j <= 360.0; j += spectrum.angle)
    {
        x = spectrum.center.x() + cos(M_PI * j / 180) * spectrum.radius;
        y = spectrum.center.y() + sin(M_PI * j / 180) * spectrum.radius;
        cur_end = QPointF(x, y);
        line.end = cur_end;
        step = drawLine(line, false, true);
        all_steps.push_back(step);
    }
}

void MainWindow::steps_count()
{
    QString spectrum_x_str = ui->lineEdit_spectrum_x->text();
    QString spectrum_y_str = ui->lineEdit_spectrum_y->text();
    QString spectrum_r_str = ui->lineEdit_spectrum_radius->text();
    QString angle_Str = ui->lineEdit_angle->text();

    if (spectrum_x_str.length() == 0 || spectrum_y_str.length() == 0 || spectrum_r_str.length() == 0 || angle_Str.length() == 0)
    {
        outputError("Error! Enter the spectrum first");
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

    QPointF center = QPointF(spectrum_x_double, spectrum_y_double);

    spectre_t spectre;
    spectre.center = center;
    spectre.angle = angle_double;
    spectre.color = line_color;
    spectre.radius = spectrum_r_double;

    std::vector<double> time;
    for (int i = DDA; i <= WY; i++)
    {
        spectre.method = (method_t) i;
        time.push_back(MeasureAverageTime(spectre));
    }

    std::ofstream out("/Users/administrator/Desktop/qt/C++/lab_03_00/time_res.txt");

    if (out.is_open())
    {
        out << spectre.radius << "\n";
        for (std::size_t i = 0; i < time.size(); i++)
            out << time[i] << "\n";
    }
    out.close();
    system("python3 /Users/administrator/Desktop/qt/C++/lab_03_00/time.py");

    outputSuccess("Success");
}

void MainWindow::time_measure()
{
    QString spectrum_x_str = ui->lineEdit_spectrum_x->text();
    QString spectrum_y_str = ui->lineEdit_spectrum_y->text();
    QString spectrum_r_str = ui->lineEdit_spectrum_radius->text();
    QString angle_Str = ui->lineEdit_angle->text();

    if (spectrum_x_str.length() == 0 || spectrum_y_str.length() == 0 || spectrum_r_str.length() == 0 || angle_Str.length() == 0)
    {
        outputError("Error! Enter the spectrum first");
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

    QPointF center = QPointF(spectrum_x_double, spectrum_y_double);

    spectre_t spectre;
    spectre.center = center;
    spectre.angle = angle_double;
    spectre.color = line_color;
    spectre.radius = spectrum_r_double;
    std::vector<int> steps;
    spectre.method = DDA;
    MeasureSteps(spectre, steps);
    spectre.method = BRESEN_DOUBLE;
    MeasureSteps(spectre, steps);
    spectre.method = BRESEN_INT;
    MeasureSteps(spectre, steps);
    spectre.method = BRESEN_STEPS;
    MeasureSteps(spectre, steps);
    spectre.method = WY;
    MeasureSteps(spectre, steps);

    double ma = spectre.angle * std::ceil(360 / spectre.angle);
    std::ofstream out("/Users/administrator/Desktop/qt/C++/lab_03_00/steps_res.txt");

    if (out.is_open())
    {
        out << spectre.radius << "\n";
        out << spectre.angle << "\n";
        out << ma << "\n";
        for (std::size_t i = 0; i < steps.size(); i++)
            out << steps[i] << "\n";
    }
    out.close();
    system("python3 /Users/administrator/Desktop/qt/C++/lab_03_00/steps.py");

    outputSuccess("Успешно");
}

double MainWindow::MeasureAverageTime(spectre_t spectrum)
{
    const int iterations = 100;
    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;
    using std::chrono::microseconds;

    auto end = high_resolution_clock::now();
    auto start = high_resolution_clock::now();
    double x, y;
    QPointF cur_end;
    line_t line;
    line.color = spectrum.color;
    line.method = spectrum.method;
    line.start = spectrum.center;

    for (int i = 0; i < iterations; i++)
    {
        for (double j = 0.0; j <= 360.0; j += spectrum.angle)
        {
            x = spectrum.center.x() + cos(M_PI * j / 180) * spectrum.radius;
            y = spectrum.center.y() + sin(M_PI * j / 180) * spectrum.radius;
            cur_end = QPointF(x, y);
            line.end = cur_end;
            drawLine(line, false, false);
        }
    }
    end = high_resolution_clock::now();
    return (double)duration_cast<microseconds>(end - start).count() / iterations;
}
