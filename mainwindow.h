#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qwt_picker.h>
#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>
#include <qwt_plot_curve.h>
#include <QPointF>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_enableSizeButton_clicked();
    void fixClickedPoint(const QPointF& point);
    void on_clearButton_clicked();
    void on_helpButton_clicked();

private:
    Ui::MainWindow *ui;
    // Массивы для хранения точек решения (plus и minus - направления от начальной точки)
    double **xnPlus, **xnMinus, **ynPlus, **ynMinus;
    // Координаты начальной точки
    double x0, y0;
    // Количество отрисованных траекторий
    int countTraj;
    // Переменная для отрисовки кривой
    QwtPlotCurve *plusCurve, *minusCurve;
    // Передает координаты клика в области отрисовки
    QwtPlotPicker *picker;

private:
    void initArrays();
    void initTauComboBox();
    void initQwtPlot();
    void initQwtPlotPicker();
    void initCurves();
    void initImageODESystem();
    void setEnabledSpinBoxes(bool isEnabled);
    void displayTrajectory(int idTraj);
    // Функции, для которых строится и рисуется примерное решение
    double func1(double xn, double yn);
    double func2(double xn, double yn);
    // Вычисление решения и занесение точек решения в массивы
    void buildTrajectory(int idTraj);
};

#endif // MAINWINDOW_H
