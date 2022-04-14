#ifndef DIALOGEXAMPLE1_H
#define DIALOGEXAMPLE1_H

#include <QDialog>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>


namespace Ui {
class DialogExample1;
}

class DialogExample1 : public QDialog
{

public:
    explicit DialogExample1(QWidget *parent = 0);
    ~DialogExample1();
    void Func1();


signals:
    void findNext(const QString &str, Qt::CaseSensitivity cs);
    void findPrevious(const QString &str, Qt::CaseSensitivity cs);


private slots:
    void findClicked();
    void enableFindButton(const QString &text);

private:
    QLabel *label;
    QLineEdit *lineEdit;
    QCheckBox *caseCheckBox;
    QCheckBox *backwardCheckBox;
    QPushButton *findButton;
    QPushButton *closeButton;
    Ui::DialogExample1 *ui;



};

#endif // DIALOGEXAMPLE1_H
