#include "modbus.h"
#include "settingsdialog.h"
#include <QUrl>

Modbus::Modbus(QObject *parent) : QObject(parent)
{
    modbusTimer = nullptr;

    m_settingsDialog = new SettingsDialog(this);
    hmi_customer_name_tlc = "Modbus Tcp-Example";
    emit getHmiCustomerNameTlcChanged();
    OutputDataKg = "0";
    emit getOutputDataKgChanged();
    onConnectButtonClicked();

    startTimer();
}

void Modbus::startTimer() {
    if (modbusTimer) {
        modbusTimer->stop();
        delete modbusTimer;
        modbusTimer = nullptr;
        qDebug() << "stopped reading";
    } else {
        modbusTimer = new QTimer();
        connect(modbusTimer, &QTimer::timeout, this, &Modbus::onReadButtonClicked);
        modbusTimer->start(100);
        qDebug() << "started reading";
    }
}

void Modbus::onConnectButtonClicked()
{
    QString modbus_server_url = m_settingsDialog->settings().modbusServerUrl;
    modbusDevice = new QModbusTcpClient(this);
    qDebug() << "modbusDevice" << modbusDevice;

    if (!modbusDevice)
        return;

    if (modbusDevice->state() != QModbusDevice::ConnectedState) {
        const QUrl url = QUrl::fromUserInput(modbus_server_url);
        modbusDevice->setConnectionParameter(QModbusDevice::NetworkPortParameter, url.port());
        modbusDevice->setConnectionParameter(QModbusDevice::NetworkAddressParameter, url.host());

        modbusDevice->setTimeout(m_settingsDialog->settings().responseTime);
        modbusDevice->setNumberOfRetries(m_settingsDialog->settings().numberOfRetries);
        if (!modbusDevice->connectDevice()) {
            qDebug() << "Connect failed: " << modbusDevice->errorString();
        } else {
            qDebug() << "connected";
        }
        qDebug() << "else connectDevice";
    } else {
        modbusDevice->disconnectDevice();
        qDebug() << "else disconnectDevice";
    }
}


QModbusDataUnit Modbus::readRequestOutputDataKg() const
{
    const auto table_kneader =
        static_cast<QModbusDataUnit::RegisterType>(QModbusDataUnit::InputRegisters);

    int startAddress = 0; //ui->readAddress->value();
    Q_ASSERT(startAddress >= 0 && startAddress < 11);

    // do not go beyond 10 entries
    quint16 numberOfEntries = 10;
    return QModbusDataUnit(table_kneader, startAddress, numberOfEntries);
}

QModbusDataUnit Modbus::readRequestCustomerName() const
{
    const auto table_customer_name =
        static_cast<QModbusDataUnit::RegisterType>(QModbusDataUnit::InputRegisters);

    int startAddress = 0; //ui->readAddress->value();
    Q_ASSERT(startAddress >= 0 && startAddress < 11);

    // do not go beyond 10 entries
    quint16 numberOfEntries = 10;
    return QModbusDataUnit(table_customer_name, startAddress, numberOfEntries);
}

void Modbus::onReadButtonClicked()
{
    if (!modbusDevice){
        qDebug()<<"Not Open Modbus-Read";
        return;
    }


    if (auto *reply_kneader = modbusDevice->sendReadRequest(readRequestOutputDataKg(), 1)) {
        if (!reply_kneader->isFinished())
            connect(reply_kneader, &QModbusReply::finished, this, &Modbus::onReadReadyOutputDataKg);
        else
            delete reply_kneader; // broadcast replies return immediately
    } else {
        qDebug() << "Read error: " << modbusDevice->errorString();
    }

    if (auto *reply_customer_name = modbusDevice->sendReadRequest(readRequestCustomerName(), 1)) {
        if (!reply_customer_name->isFinished())
            connect(reply_customer_name, &QModbusReply::finished, this, &Modbus::onReadReadyCustomerName);
        else
            delete reply_customer_name; // broadcast replies return immediately
    } else {
        qDebug() << "Read error: " << modbusDevice->errorString();
    }
}

void Modbus::onReadReadyOutputDataKg()
{
    auto reply_kneader = qobject_cast<QModbusReply *>(sender());
    if (!reply_kneader)
        return;

    if (reply_kneader->error() == QModbusDevice::NoError) {
        qDebug() << "reply_kneader->error() == QModbusDevice::NoError";
        const QModbusDataUnit unit_kneader = reply_kneader->result();
        for (int i = 0, total = int(unit_kneader.valueCount()); i < total; ++i) {
            const QString entry = tr("Address: %1, Value: %2").arg(unit_kneader.startAddress() + i)
                                     .arg(QString::number(unit_kneader.value(i),
                                          unit_kneader.registerType() <= QModbusDataUnit::InputRegisters ? 10 : 16));
            qDebug()<<entry<<"Deneme-Test";
            if (unit_kneader.startAddress() + i == 2) {
                OutputDataKg = QString::number(unit_kneader.value(i));
                qDebug() << "MB_ADDRESS_NET_WEIGHT_LOW : " << OutputDataKg;
                emit getOutputDataKgChanged();
            }
        }
    } else if (reply_kneader->error() == QModbusDevice::ProtocolError) {
        qDebug() << "Read response error - onReadReadyKneader: " << reply_kneader->errorString() << reply_kneader->rawResult().exceptionCode()<<"ProtokolError";
    } else {
        qDebug() << "Read response error - onReadReadyKneader: " << reply_kneader->errorString() << reply_kneader->error()<<"Unknow Error";
    }

    reply_kneader->deleteLater();
}

void Modbus::onReadReadyCustomerName()
{
    auto reply_customer_name = qobject_cast<QModbusReply *>(sender());
    if (!reply_customer_name)
        return;

    if (reply_customer_name->error() == QModbusDevice::NoError) {
        const QModbusDataUnit unit_customer_name = reply_customer_name->result();
        hmi_customer_name_tlc = "";
        for (int i = 0, total = int(unit_customer_name.valueCount()); i < total; ++i) {
            const QString entry = tr("Address: %1, Value: %2").arg(unit_customer_name.startAddress() + i)
                                     .arg(QString::number(unit_customer_name.value(i),
                                          unit_customer_name.registerType() <= QModbusDataUnit::InputRegisters ? 10 : 16));
            qDebug()<<entry<<"Test-2";
            if (unit_customer_name.startAddress() + i == 0) {
                hmi_customer_name_tlc.append(QString::number(unit_customer_name.value(i)));
            }
            if (unit_customer_name.startAddress() + i == 1) {
                hmi_customer_name_tlc.append(QString::number(unit_customer_name.value(i)));
            }
            if (unit_customer_name.startAddress() + i == 2) {
                hmi_customer_name_tlc.append(QString::number(unit_customer_name.value(i)));
            }
            if (unit_customer_name.startAddress() + i == 3) {
                hmi_customer_name_tlc.append(QString::number(unit_customer_name.value(i)));
            }
            if (unit_customer_name.startAddress() + i == 4) {
                hmi_customer_name_tlc.append(QString::number(unit_customer_name.value(i)));
            }
            if (unit_customer_name.startAddress() + i == 5) {
                hmi_customer_name_tlc.append(QString::number(unit_customer_name.value(i)));
            }
            if (unit_customer_name.startAddress() + i == 6) {
                hmi_customer_name_tlc.append(QString::number(unit_customer_name.value(i)));
            }
            if (unit_customer_name.startAddress() + i == 7) {
                hmi_customer_name_tlc.append(QString::number(unit_customer_name.value(i)));
            }
            if (unit_customer_name.startAddress() + i == 8) {
                hmi_customer_name_tlc.append(QString::number(unit_customer_name.value(i)));
            }
            if (unit_customer_name.startAddress() + i == 9) {
                hmi_customer_name_tlc.append(QString::number(unit_customer_name.value(i)));
            }
        }
        hmi_customer_name_tlc = hmi_customer_name_tlc.trimmed();
        qDebug()<<hmi_customer_name_tlc;
        qDebug() << "Customer Name: " << hmi_customer_name_tlc;
        emit getHmiCustomerNameTlcChanged();
    } else if (reply_customer_name->error() == QModbusDevice::ProtocolError) {
        qDebug() << "Read response error - onReadReadyCustomerName: " << reply_customer_name->errorString() << reply_customer_name->rawResult().exceptionCode()<<"Protokol";
    } else {
        qDebug() << "Read response error - onReadReadyCustomerName: " << reply_customer_name->errorString() << reply_customer_name->error()<<"Sorun belli değil";
    }

    reply_customer_name->deleteLater();
}

QString Modbus::getHmiCustomerNameTlc()
{
    return hmi_customer_name_tlc;
}

QString Modbus::getOutputDataKg()
{
    return OutputDataKg;
}


// write functions
void Modbus::onWriteButtonClicked(int writeregister)
{
    // writeregister = 1 -> setpoint_kneader_temperature
    // writeregister = 2 -> washing_ev_command
    // writeregister = 3 -> customer_name
    if (!modbusDevice)
        return;

    QModbusDataUnit writeUnit;
    QBitArray m_coils(1);
    m_holdingRegisters.clear();
    switch (writeregister) {
        case 1: {
            break;
        }
        case 2: {
            break;
        }
        case 3: {
            qDebug()<<"Using case 3";
            QString StrData = "Interelectronix e.K.                                                          ";
            //qDebug() << "before " << StrData;
            QStringList numberString;
            for(const auto character: StrData){
                numberString << QString::number(character.unicode(), 10);
            }
            QString HexStrData= numberString.join(", ");

            //qDebug() << HexStrData;
            for (int i = 0, total = int(numberString.length()); i < total; ++i) {
                m_holdingRegisters.append(qint16(numberString[i].toInt()));
            }

            writeUnit = writeRequestCustomerName();
            break;
        }
    }

    QModbusDataUnit::RegisterType table = writeUnit.registerType();
    qDebug() << "table: " << writeUnit.registerType();
    qDebug() << "writeUnit.valueCount(): " << writeUnit.valueCount();
    for (int i = 0, total = int(writeUnit.valueCount()); i + writeUnit.startAddress() < writeUnit.startAddress() + total; ++i) {
        switch (writeregister) {
            case 1: {
                writeUnit.setValue(i, m_holdingRegisters[i]);
                break;
            }
            case 2: {
                writeUnit.setValue(i, m_coils[i]);
                break;
            }
            case 3: {
                writeUnit.setValue(i, m_holdingRegisters[i]);
                break;
            }
        }
    }

    if (auto *reply = modbusDevice->sendWriteRequest(writeUnit, 1)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, [this, reply]() {
                if (reply->error() == QModbusDevice::ProtocolError) {
                    qDebug() << "Read response error - onWriteButtonClicked: " << reply->errorString() << reply->rawResult().exceptionCode();
                } else if (reply->error() != QModbusDevice::NoError) {
                    qDebug() << "Read response error - onWriteButtonClicked: " << reply->errorString() << reply->rawResult().exceptionCode();
                }
                reply->deleteLater();
            });
        } else {
            // broadcast replies return immediately
            reply->deleteLater();
        }
    } else {
        qDebug() << "Read response error - onWriteButtonClicked: " << reply->errorString() << reply->error();
    }
}

QModbusDataUnit Modbus::writeRequestCustomerName() const
{
    const auto table =
        static_cast<QModbusDataUnit::RegisterType>(QModbusDataUnit::InputRegisters);

    int startAddress = 0;
    Q_ASSERT(startAddress >= 0 && startAddress < 11);

    // do not go beyond 10 entries
    quint16 numberOfEntries = 10;
    return QModbusDataUnit(table, startAddress, numberOfEntries);
}

