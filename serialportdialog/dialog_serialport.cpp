#include "dialog_serialport.h"
#include "ui_dialog_serialport.h"

Dialog_SerialPort::Dialog_SerialPort(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_SerialPort)
{
    ui->setupUi(this);

    m_speedList.append("9600");
    m_speedList.append("19200");
    m_speedList.append("38400");
    m_speedList.append("57600");
    m_speedList.append("115200");
    ui->comboBox_Speed->addItems(m_speedList);
    m_dataBitsList.append("8");
    ui->comboBox_DataBits->addItems(m_dataBitsList);
    m_parityList.append("None");
    ui->comboBox_Parity->addItems(m_parityList);
    m_flowControlList.append("None");
    ui->comboBox_FlowControl->addItems(m_flowControlList);
    m_stopBitsList.append("1");
    m_stopBitsList.append("2");
    ui->comboBox_StopBits->addItems(m_stopBitsList);
    m_portList.append("N/A");
    ui->comboBox_Port->addItems(m_portList);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(handleAccepted()));
}

Dialog_SerialPort::~Dialog_SerialPort()
{
    delete ui;
}

void Dialog_SerialPort::setPortList(QStringList portList)
{
    if (!portList.isEmpty())
    {
        m_portList = portList;
        ui->comboBox_Port->clear();
        ui->comboBox_Port->addItems(m_portList);
    }
}

QChar Dialog_SerialPort::getParityChar(QSerialPort::Parity p)
{
    static QMap<QSerialPort::Parity, QChar> m_parityCharMap;
    if (m_parityCharMap.isEmpty())
    {
        m_parityCharMap.insert(QSerialPort::NoParity, 'N');
        m_parityCharMap.insert(QSerialPort::EvenParity, 'E');
        m_parityCharMap.insert(QSerialPort::OddParity, 'O');
        m_parityCharMap.insert(QSerialPort::SpaceParity, 'S');
        m_parityCharMap.insert(QSerialPort::MarkParity, 'M');
        m_parityCharMap.insert(QSerialPort::UnknownParity, 'U');
    }
    return m_parityCharMap.value(p, 'U');
}

// OK button clicked
void Dialog_SerialPort::handleAccepted()
{
    emit setSerialPort(ui->comboBox_Port->currentText(),
                       (QSerialPort::BaudRate)ui->comboBox_Speed->currentText().toInt(),
                       QSerialPort::Data8,
                       QSerialPort::NoFlowControl,
                       QSerialPort::NoParity,
                       QSerialPort::OneStop);
}
