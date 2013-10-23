#include "mainwindow.h"
#include "ui_mainwindow.h"

const int NMAX = 10000;
const int M = 500;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    countTraj = 0;
    initQwtPlot();
    initQwtPlotPicker();
    initTauComboBox();
    initArrays();
    connect(picker, SIGNAL(selected(const QPointF&)),
            this, SLOT(fixClickedPoint(const QPointF&)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_enableSizeButton_clicked() {
    ui->qwtPlot->setAxisScale(
                QwtPlot::xBottom,
                std::min(ui->aDoubleSpinBox->value(), ui->bDoubleSpinBox->value()),
                std::max(ui->aDoubleSpinBox->value(), ui->bDoubleSpinBox->value()));
    ui->qwtPlot->setAxisScale(
                QwtPlot::yLeft,
                std::min(ui->cDoubleSpinBox->value(), ui->dDoubleSpinBox->value()),
                std::max(ui->cDoubleSpinBox->value(), ui->dDoubleSpinBox->value()));
    ui->qwtPlot->replot();
}

void MainWindow::initArrays() {
    xnPlus = new double* [M];
    xnMinus = new double* [M];
    ynPlus = new double* [M];
    ynMinus = new double* [M];
    for (int i = 0; i < M; i++) {
        xnPlus[i] = new double [NMAX];
    }
    for (int i = 0; i < M; i++) {
        xnMinus[i] = new double [NMAX];
    }
    for (int i = 0; i < M; i++) {
        ynPlus[i] = new double [NMAX];
    }
    for (int i = 0; i < M; i++) {
        ynMinus[i] = new double [NMAX];
    }
}

void MainWindow::initTauComboBox() {
    QStringList tauList;
    tauList << "1" << "0.1" << "0.01" << "0.001" << "0.0001";
    ui->tauComboBox->addItems(tauList);
}

void MainWindow::initQwtPlot() {
    ui->qwtPlot->setTitle("Графики траекторий");
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom,
                              ui->aDoubleSpinBox->value(),
                              ui->bDoubleSpinBox->value());
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft,
                              ui->cDoubleSpinBox->value(),
                              ui->dDoubleSpinBox->value());
}

void MainWindow::initQwtPlotPicker() {
    picker = new QwtPlotPicker(ui->qwtPlot->canvas());
    picker->setTrackerMode(QwtPicker::AlwaysOn);
    picker->setRubberBandPen(QColor(Qt::red));
    picker->setRubberBand(QwtPicker::NoRubberBand);
    picker->setStateMachine(new QwtPickerClickPointMachine());
    picker->setMousePattern(QwtPicker::MouseSelect1, Qt::LeftButton);
}

void MainWindow::initCurves() {
    QPen plusPen = QPen(QColor(Qt::red));
    QPen minusPen = QPen(QColor(Qt::blue));
    plusCurve = new QwtPlotCurve();
    minusCurve = new QwtPlotCurve();
    plusCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
    minusCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
    plusCurve->setPen(plusPen);
    minusCurve->setPen(minusPen);
    plusCurve->attach(ui->qwtPlot);
    minusCurve->attach(ui->qwtPlot);
}

double MainWindow::func1(double xn, double yn) {
    return ui->alphaDoubleSpinBox->value() * xn
            + ui->betaDoubleSpinBox->value() * yn
            + ui->epsilonDoubleSpinBox->value();
}

double MainWindow::func2(double xn) {
    return ui->lyambdaDoubleSpinBox->value() * xn
            + ui->fiDoubleSpinBox->value();
}

void MainWindow::buildTrajectory(int idTraj) {
    for (int i = 1; i <= ui->nDoubleSpinBox->value(); i++) {
        xnPlus[idTraj][i] = xnPlus[idTraj][i -1]
                + ui->tauComboBox->currentText().toDouble()
                * func1(xnPlus[idTraj][i -1], ynPlus[idTraj][i - 1]);
        xnMinus[idTraj][i] = xnMinus[idTraj][i -1]
                - ui->tauComboBox->currentText().toDouble()
                * func1(xnMinus[idTraj][i -1], ynMinus[idTraj][i - 1]);
        ynPlus[idTraj][i] = ynPlus[idTraj][i -1]
                + ui->tauComboBox->currentText().toDouble()
                * func2(xnPlus[idTraj][i -1]);
        ynMinus[idTraj][i] = ynMinus[idTraj][i -1]
                - ui->tauComboBox->currentText().toDouble()
                * func2(xnMinus[idTraj][i -1]);
    }
}

void MainWindow::fixClickedPoint(const QPointF& point) {
    xnPlus[countTraj][0] = point.x();
    xnMinus[countTraj][0] = point.x();
    ynPlus[countTraj][0] = point.y();
    ynMinus[countTraj][0] = point.y();
    initCurves();
    buildTrajectory(countTraj);
    displayTrajectory(countTraj);
    countTraj++;
}

void MainWindow::displayTrajectory(int idTraj) {
    plusCurve->setSamples(xnPlus[idTraj], ynPlus[idTraj],
                          ui->nDoubleSpinBox->value() + 1);
    minusCurve->setSamples(xnMinus[idTraj], ynMinus[idTraj],
                           ui->nDoubleSpinBox->value() + 1);
    ui->qwtPlot->replot();
}

void MainWindow::on_clearButton_clicked() {
    ui->qwtPlot->detachItems(QwtPlotItem::Rtti_PlotCurve);
    ui->qwtPlot->replot();
}
