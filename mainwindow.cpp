#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , serial(new QSerialPort(this))
{
    ui->setupUi(this);

    series = new QLineSeries(); // Đã bỏ QtCharts::
    chart = new QChart(); // Đã bỏ QtCharts::
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle("Biểu đồ Nhiệt độ theo thời gian");

    QValueAxis *axisX = new QValueAxis; // Đã bỏ QtCharts::
    axisX->setLabelFormat("%d");
    axisX->setTitleText("Time (s)");
    axisX->setTickCount(10);

    QValueAxis *axisY = new QValueAxis; // Đã bỏ QtCharts::
    axisY->setLabelFormat("%.1f");
    axisY->setTitleText("Temperature (°C)");
    axisY->setRange(0, 100);

    chart->setAxisX(axisX, series);
    chart->setAxisY(axisY, series);

    chartView = new QChartView(chart); // Đã bỏ QtCharts::
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->verticalLayout->addWidget(chartView);

    serial->setPortName("COM3"); // Chỉnh đúng COM của Arduino
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->open(QIODevice::ReadOnly);

    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readSerial);
}
