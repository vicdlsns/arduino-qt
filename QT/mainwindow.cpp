#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Create Object the Class QSerialPort*/
        serialPort = new QSerialPort(this);

        /* Create Object the Class Arduino to manipulate read/write*/
        arduino = new Arduino(serialPort);

        ui->pbDisconnect->setEnabled(false);
        ui->pbConnect->setEnabled(false);
        ui->pbLed->setEnabled(false);

        on_pbUpdatePorts_clicked();

        /* Connect Objects -> Signal and Slots
         */
        connect(serialPort, SIGNAL(readyRead()), this, SLOT(ReadData()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbConnect_clicked()
{
    bool statusOpenSerial;

        statusOpenSerial = arduino->Connect(ui->cbDevice->currentText(),
                                                 ui->cbBaudRate->currentText().toInt()
                                                 );
        if (statusOpenSerial) {
            ui->pbDisconnect->setEnabled(true);
            ui->pbConnect->setEnabled(false);
            ui->pbLed->setEnabled(true);
            qDebug() << "Device connected without errors!";
        }
        else {
            qDebug() << "Error connecting the device!";
        }
}

void MainWindow::on_pbDisconnect_clicked()
{
    bool statusCloseSerial;


        statusCloseSerial = arduino->Disconnect();

        if (statusCloseSerial) {
            ui->pbDisconnect->setEnabled(false);
            ui->pbConnect->setEnabled(true);
            ui->pbLed->setEnabled(false);
            qDebug() << "Device disconnected without errors!";
        }
        else {
            qDebug() << "Error disconnecting the device!";
        }
}

void MainWindow::WriteData(const QByteArray data)
{
    arduino->Write(data);
}

void MainWindow::ReadData()
{

        QString received = arduino->Read();
        qDebug() << "received data:" << received;


        if (received==ARDUINO_TURNED_LED_ON)
        {
            qDebug() << "led on";
        }

        else if (received==ARDUINO_TURNED_LED_OFF)
        {
            qDebug() << "led off";
        }

}

void MainWindow::on_pbLed_clicked()
{
    WriteData(PC_REQUESTED_LED_STATE_CHANGE);
}

void MainWindow::on_pbUpdatePorts_clicked()
{
    bool statusCloseSerial;


        statusCloseSerial = arduino->Disconnect();


        if (statusCloseSerial) {


                /* Load available devices */
                QStringList devices = arduino->loadDevices();

                /* Inserting in ComboxBox */
                ui->cbDevice->clear();
                ui->cbDevice->addItems(devices);

                /* Enable PushButton "Connect" if any port is found.
                 */
                if(ui->cbDevice->count() > 0) {
                    ui->pbConnect->setEnabled(true);
                    ui->pbDisconnect->setEnabled(false);
                    qDebug() << "Device ready!";
                }
                else {
                    ui->pbDisconnect->setEnabled(false);
                    ui->pbConnect->setEnabled(false);
                    ui->pbLed->setEnabled(false);
                    qDebug() << "Devices not found!"; }
        }
        else {
            qDebug() << "Error disconnecting the device!";
        }
}
