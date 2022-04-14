#include "dialogexample1.h"
#include "ui_dialogexample1.h"

DialogExample1::DialogExample1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogExample1)
{
    ui->setupUi(this);
}

DialogExample1::~DialogExample1()
{
    delete ui;
}
