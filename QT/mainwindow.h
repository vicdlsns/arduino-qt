#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "arduino.h"

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
    void on_pbConnect_clicked();
    void on_pbDisconnect_clicked();

    void WriteData(const QByteArray data);
    void ReadData();

    void on_pbLed_clicked();

    void on_pbUpdatePorts_clicked();

private:
    Ui::MainWindow *ui;

    QSerialPort *serialPort;
    Arduino *arduino;
};

#endif // MAINWINDOW_H
