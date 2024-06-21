#ifndef EXTENSIONDIALOG_H
#define EXTENSIONDIALOG_H

#include <ui_extensiondialog.h>
#include <QDialog>

namespace Ui {
class ExtensionDialog;
}

class ExtensionDialog : public QDialog, public Ui::ExtensionDialog
{
    Q_OBJECT

public:
    explicit ExtensionDialog(QWidget *parent = 0);
    void setColumnRange(QChar first, QChar last);

};

#endif // EXTENSIONDIALOG_H
