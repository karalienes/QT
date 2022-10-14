#ifndef MODBUS_H
#define MODBUS_H

#include <QDebug>
#include <QModbusClient>
#include <QModbusDataUnit>
#include <QModbusReply>
#include <QModbusRtuSerialMaster>
#include <QModbusTcpClient>
#include <QObject>
#include <QTimer>
#include <QtSerialPort/QSerialPort>
#include <QtGlobal>
#include <QBitArray>

//class WriteRegisterModel;
class SettingsDialog;

class Modbus : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString hmi_customer_name_tlc READ getHmiCustomerNameTlc NOTIFY getHmiCustomerNameTlcChanged)
    Q_PROPERTY(QString OutputDataKg READ getOutputDataKg NOTIFY getOutputDataKgChanged)

public:
    explicit Modbus(QObject *parent = nullptr);

    Q_INVOKABLE void onReadButtonClicked();
    Q_INVOKABLE void onWriteButtonClicked(int writeregister);

    // variables
    QString hmi_customer_name_tlc;
    static inline QString OutputDataKg;

    QVector<quint16> m_holdingRegisters;

private:
    QModbusClient *modbusDevice = nullptr;
    //WriteRegisterModel *writeModel = nullptr;
    SettingsDialog *m_settingsDialog = nullptr;

    QModbusDataUnit readRequestOutputDataKg() const;
    QModbusDataUnit readRequestCustomerName() const;

    QModbusDataUnit writeRequestCustomerName() const;

    void onConnectButtonClicked();

    void onReadReadyOutputDataKg();
    void onReadReadyCustomerName();

    //variables
    QString getHmiCustomerNameTlc();
    QString getOutputDataKg();


    QTimer *modbusTimer;
    void startTimer();

signals:
    //variables
    void getHmiCustomerNameTlcChanged();
    void getOutputDataKgChanged();
};

#endif // MODBUS_H
