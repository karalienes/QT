#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QObject>
#include <QSettings>
#include <QDebug>

class SettingsDialog : public QObject
{
    Q_OBJECT

public:
    struct Settings {
        QString modbusServerUrl = "192.168.151.92:502";
        int responseTime = 1000;
        int numberOfRetries = 3;
    };

    explicit SettingsDialog(QObject *parent = nullptr);

    Settings settings() const;

private:
    Settings m_settings;
};

#endif // SETTINGSDIALOG_H
