#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    modbus = new Modbus(this);
    QObject::connect(modbus,SIGNAL(getOutputDataKgChanged()),this,SLOT(OutputKgSlotFunc()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->label->setText(modbus->OutputDataKg);
    QString barcode = ui->lineEdit->text();
    auto zint = ZBarcode_Create();
    zint->symbology = BARCODE_CODE128;
    ZBarcode_Encode(zint, reinterpret_cast<const uint8_t*>(barcode.toLatin1().data()), 0);
    ZBarcode_Print(zint, 0); // this saves the generated barcode to "out.png"
    ZBarcode_Delete(zint);
    QPixmap pix(QDir::currentPath()+"/out.png");
    ui->label_2->setPixmap(pix);


}

void MainWindow::OutputKgSlotFunc()
{
    ui->lineEdit->setText(modbus->OutputDataKg);

}

