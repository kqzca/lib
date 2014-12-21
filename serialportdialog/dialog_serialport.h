#ifndef DIALOG_SERIALPORT_H
#define DIALOG_SERIALPORT_H

#include <QDialog>
#include <QtSerialPort/QtSerialPort>

namespace Ui {
class Dialog_SerialPort;
}

class Dialog_SerialPort : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_SerialPort(QWidget *parent = 0);
    ~Dialog_SerialPort();
    void setPortList(QStringList portList);
    static QChar getParityChar(QSerialPort::Parity p);

signals:
    void setSerialPort(QString,
                       QSerialPort::BaudRate,
                       QSerialPort::DataBits,
                       QSerialPort::FlowControl,
                       QSerialPort::Parity,
                       QSerialPort::StopBits);

private slots:
    void handleAccepted();

private:
    Ui::Dialog_SerialPort *ui;
    QStringList m_portList, m_speedList, m_dataBitsList, m_parityList, m_stopBitsList, m_flowControlList;
};

#endif // DIALOG_SERIALPORT_H
