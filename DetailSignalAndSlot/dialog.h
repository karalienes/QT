#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class GotoCellDialog;
}

class Dialog : public QDialog
{


public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::GotoCellDialog *ui;


private slots:
    void on_lineEdit_textChanged();
    void okButton();

};

#endif // DIALOG_H
