#ifndef GOTOCELLDIALOG_H
#define GOTOCELLDIALOG_H

#include <QDialog>
#include "ui_dialog.h"

class gotocelldialog : public QDialog , public Ui::GotoCellDialog
{
    Q_OBJECT
public:
    gotocelldialog(QWidget * parent =0);

private slots:
    void on_lineEdit_textChanged();

};

#endif // GOTOCELLDIALOG_H
