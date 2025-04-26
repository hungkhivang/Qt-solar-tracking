#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Chọn một trong hai cách sau:
// Cách 1: Sử dụng namespace
QT_CHARTS_USE_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void readSerial();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    QByteArray serialBuffer;
    QLineSeries *series; // Đã bỏ QtCharts::
    QChart *chart; // Đã bỏ QtCharts::
    QChartView *chartView; // Đã bỏ QtCharts::
    int timeX = 0;
};

#endif // MAINWINDOW_H
