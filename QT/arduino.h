#ifndef ARDUINO_H
#define ARDUINO_H

#define ARDUINO_TURNED_LED_ON "LEDON"
#define ARDUINO_TURNED_LED_OFF "LEDOFF"
#define PC_REQUESTED_LED_STATE_CHANGE u8"CHANGELED"

#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class Arduino
{
public:
    Arduino(QSerialPort *port);
    ~Arduino();

    QStringList loadDevices();

    bool Connect(QString Port, uint32_t baudRate);
    bool Disconnect(void);

    qint64 Write(const char *cmd);
    QString Read();
    QString Read(int BufferSize);
    QByteArray ReadBytes();

protected:
    QSerialPort *serialPort;

};

#endif // ARDUINO_H
