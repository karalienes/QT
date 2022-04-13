#include "drawing.h"
#include "ui_drawing.h"

Drawing::Drawing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Drawing)
{
    ui->setupUi(this);
}

Drawing::~Drawing()
{
    delete ui;
}
