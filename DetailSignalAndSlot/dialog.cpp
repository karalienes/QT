#include "dialog.h"
#include "ui_dialog.h"
#include <QtGui>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GotoCellDialog)
{
    ui->setupUi(this);

//    QRegExp regExp("[A-Za-z][1-9][0-9]{0-2}");
//    ui->lineEdit->setValidator(new QRegExpValidator(regExp,this));


    QObject::connect(ui->okButton,SIGNAL(clicked(bool)),this,SLOT(accept()));
    QObject::connect(ui->cancelButton,SIGNAL(clicked(bool)),this,SLOT(reject()));
    QObject::connect(ui->lineEdit, SIGNAL(textChanged(QString)),this,SLOT(on_lineEdit_textChanged()));

}
Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_lineEdit_textChanged()
{
    ui->okButton->setEnabled(ui->lineEdit->hasAcceptableInput());
}

void Dialog::okButton()
{
    this->ui->okButton->setEnabled(false);
}
