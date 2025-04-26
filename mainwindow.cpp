#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , serial(new QSerialPort(this))
{
    ui->setupUi(this);

    series = new QtCharts::QLineSeries();
    chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle("Biểu đồ Nhiệt độ theo thời gian");

    QtCharts::QValueAxis *axisX = new QtCharts::QValueAxis;
    axisX->setLabelFormat("%d");
    axisX->setTitleText("Time (s)");
    axisX->setTickCount(10);

    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis;
    axisY->setLabelFormat("%.1f");
    axisY->setTitleText("Temperature (°C)");
    axisY->setRange(0, 100);

    chart->setAxisX(axisX, series);
    chart->setAxisY(axisY, series);

    chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->verticalLayout->addWidget(chartView);

    serial->setPortName("COM3"); // Chỉnh đúng COM của Arduino
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->open(QIODevice::ReadOnly);

    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readSerial);
}

void MainWindow::readSerial() {
    serialBuffer.append(serial->readAll());

    if (serialBuffer.contains('\n')) {
        QString data = QString::fromUtf8(serialBuffer).trimmed();
        serialBuffer.clear();

        QStringList parts = data.split(',');
        if (parts.size() == 3) {
            QString temp = parts[0].split(':')[1];
            QString hori = parts[1].split(':')[1];
            QString vert = parts[2].split(':')[1];

            ui->labelTemp->setText("Nhiệt độ: " + temp + " °C");
            ui->labelHori->setText("Servo ngang: " + hori + "°");
            ui->labelVert->setText("Servo dọc: " + vert + "°");

            qreal tempVal = temp.toFloat();
            series->append(timeX++, tempVal);

            if (series->count() > 50) {
                series->remove(0);
            }
        }
    }
}

MainWindow::~MainWindow() {
    serial->close();
    delete ui;
}