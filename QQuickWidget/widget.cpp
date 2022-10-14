#include "widget.h"
#include "ui_widget.h"
#include <QQmlContext>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->quickWidget->rootContext()->setContextProperty("mainWidget",this);
    ui->quickWidget->setSource(QUrl(QStringLiteral("/home/karali/QQuickWidget/widget.qml")));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::printTextColor(const QString &textColor)
{
    ui->lineEdit->setText(textColor);
}

