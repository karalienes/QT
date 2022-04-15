#include "dialogexample1.h"
#include "ui_dialogexample1.h"

DialogExample1::DialogExample1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogExample1)
{
    ui->setupUi(this);
    this->Func1();

}

DialogExample1::~DialogExample1()
{
    delete ui;
}


void DialogExample1::Func1()
{
    label = new QLabel(tr("Find &What:"));
    lineEdit = new QLineEdit;
    label->setBuddy(lineEdit);

    caseCheckBox = new QCheckBox(tr("Match &case"));
    backwardCheckBox = new QCheckBox(tr("Search &backward"));


    findButton = new QPushButton(tr("&Find"));
    setMinimumSize(200,200);
    findButton->setDefault(true);
    findButton->setEnabled(false);



    QObject::connect(lineEdit, SIGNAL(textChanged(QString)),this,SLOT(enableFindButton(QString)));
    QObject::connect(findButton, SIGNAL(clicked(bool)),this,SLOT(findClicked()));
    QObject::connect(closeButton, SIGNAL(clicked(bool)),this, SLOT(close()));

//    this->Func2();

}


void DialogExample1::Func2()
{




    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(label);
    topLeftLayout->addWidget(lineEdit);

    QVBoxLayout *leftLayout = new  QVBoxLayout;
    leftLayout->addLayout(topLeftLayout);
    leftLayout->addWidget(caseCheckBox);
    leftLayout->addWidget(backwardCheckBox);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(findButton);
    rightLayout->addWidget(closeButton);

    //Bu kutu düzeninin sonuna sıfır minimum boyut ve esneme faktörü esnetme ile gerilebilir bir alan (bir QSpacerItem) ekler.
    rightLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);



    setWindowTitle(tr("Find"));
    setFixedHeight(sizeHint().height());

}

void DialogExample1::findClicked()
{
    QString text =lineEdit->text();

    Qt::CaseSensitivity cs =
            caseCheckBox->isChecked() ? Qt::CaseSensitive
                                      : Qt::CaseInsensitive;

    if(backwardCheckBox->isChecked()){
        emit findPrevious(text,cs);
    }

    else {
        emit findNext(text,cs);
    }

}

void DialogExample1::enableFindButton(const QString &text)
{
    findButton->setEnabled(!text.isEmpty());
}






