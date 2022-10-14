#include "settingsdialog.h"

SettingsDialog::SettingsDialog(QObject *parent) : QObject(parent)
{
    //readSettings();
}

SettingsDialog::Settings SettingsDialog::settings() const
{
    return m_settings;
}
