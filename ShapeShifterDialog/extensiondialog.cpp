#include "extensiondialog.h"
#include "ui_extensiondialog.h"
#include <QtGui>

ExtensionDialog::ExtensionDialog(QWidget *parent) :
    QDialog(parent)
{

   setupUi(this);
   secondaryGroupBox->hide();
   tertiaryGroupBox->hide();
   //çalışması için ızgara mod açılmaldıır.
   layout()->setSizeConstraint(QLayout::SetFixedSize);

   setColumnRange('A', 'Z');
   QObject::connect(moreButton, SIGNAL(clicked(bool)),secondaryGroupBox,SLOT(setHidden(bool)));
   QObject::connect(moreButton, SIGNAL(clicked(bool)), tertiaryGroupBox , SLOT(setHidden(bool)));
}


void ExtensionDialog::setColumnRange(QChar first, QChar last)
{
    primaryColumnCombo->clear();
    secondaryColumnCombo->clear();
    tertiaryColumnCombo->clear();

    secondaryColumnCombo->addItem(tr("None"));
    tertiaryColumnCombo->addItem(tr("None"));
    primaryColumnCombo->setMinimumSize(secondaryColumnCombo->sizeHint());

    QChar ch= first;

    while(ch<= last){

        primaryColumnCombo->addItem(QString(ch));
        secondaryColumnCombo->addItem(QString(ch));
        tertiaryColumnCombo->addItem(QString(ch));

        ch=ch.unicode()+1;
    }
}
