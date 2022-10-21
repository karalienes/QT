#include "yourage.h"
#include "ui_yourage.h"

YourAge::YourAge(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::YourAge)
{
    ui->setupUi(this);
}

YourAge::~YourAge()
{
    delete ui;
}


void YourAge::YourAgeFunc()
{

    QWidget *window =new QWidget;
    window->setWindowTitle("Enter Your Age");


    QSpinBox *spinbox = new QSpinBox;

    QSlider *slider = new QSlider(Qt::Horizontal);

    spinbox->setRange(0,130);
    slider->setRange(0,130);

    QObject::connect(spinbox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));

    QObject::connect(slider , SIGNAL(valueChanged(int)), spinbox, SLOT(setValue(int)));


    QHBoxLayout *layout =new QHBoxLayout;
    layout->addWidget(spinbox);
    layout->addWidget(slider);

    window->setLayout(layout);

    window->show();




}
