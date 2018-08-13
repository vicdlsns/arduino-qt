#include "arduino.h"

Arduino::Arduino(QSerialPort *port)
{
     serialPort = port;
}

QStringList Arduino::loadDevices()
{
    QStringList devs;

    foreach (const QSerialPortInfo info, QSerialPortInfo::availablePorts()) {

       serialPort->setPort(info);


        if (serialPort->open(QIODevice::ReadWrite)) {
            serialPort->close();
            devs << info.portName();
        }

    }
    return devs;
}

bool Arduino::Connect(QString Port, uint32_t baudRate)
{
    /* Device Serial Port */
    serialPort->setPortName(Port);
    qDebug() << "Serial Port Device: " << Port;


     /* Connect SerialPort */

        /* BaudRate */
        switch (baudRate) {
        case 2400:
            qDebug() << "Baudrate: 2400";
            serialPort->setBaudRate(QSerialPort::Baud2400);
            break;
        case 4800:
            qDebug() << "Baudrate: 4800";
            serialPort->setBaudRate(QSerialPort::Baud4800);
            break;
        case 9600:
            qDebug() << "Baudrate: 9600";
            serialPort->setBaudRate(QSerialPort::Baud9600);
            break;
        case 19200:
            qDebug() << "Baudrate: 19200";
            serialPort->setBaudRate(QSerialPort::Baud19200);
            break;
        case 115200:
            qDebug() << "Baudrate: 115200";
            serialPort->setBaudRate(QSerialPort::Baud115200);
            break;
        }

        /* FlowControl */
        serialPort->setFlowControl(QSerialPort::NoFlowControl);


        /* Other settings */
        serialPort->setDataBits(QSerialPort::Data8);
        serialPort->setParity(QSerialPort::NoParity);
        serialPort->setStopBits(QSerialPort::OneStop);


        if(serialPort->open(QIODevice::ReadWrite)) {
            qDebug() << "Serial Port opened without errors!";
            return true;
        }
        else {
            qDebug() << "Error: " << serialPort->error();
            return false;
        }
}

bool Arduino::Disconnect()
{
    serialPort->clear();
    serialPort->close();


    if(serialPort->error() == 0 || !serialPort->isOpen()) {
        qDebug() << "Serial Port closed without errors!";
        return true;
    }
    else {
        qDebug() << "Error: " << serialPort->error();
        return false;
    }
}

qint64 Arduino::Write(const char *cmd)
{
    qint64 writtenSize;
    writtenSize = serialPort->write(cmd,qstrlen(cmd));

    return writtenSize;
}

QString Arduino::Read()
{
    QString bufRxSerial;

    qDebug() << "bytes available:" << serialPort->bytesAvailable();

    /* Awaits read all the data before continuing */
    while (serialPort->waitForReadyRead(20)) {
        bufRxSerial += serialPort->readAll();
    }

    return bufRxSerial;
}

QString Arduino::Read(int BufferSize)
{
    char buf[BufferSize];

    if (serialPort->canReadLine()) {
        serialPort->read(buf, sizeof(buf));
    }

    return buf;
}

QByteArray Arduino::ReadBytes()
{
    QByteArray bufRxSerial;

    /* Awaits read all the data before continuing */
    while (serialPort->waitForReadyRead(20)) {
        bufRxSerial.append(serialPort->readAll());
    }

    return bufRxSerial;
}
