#ifndef DIALOGEXAMPLE1_H
#define DIALOGEXAMPLE1_H

#include <QDialog>

class QLabel;
class QCheckBox;
class QLineEdit;
class QPushButton;


namespace Ui {
class DialogExample1;
}

class DialogExample1 : public QDialog
{
    Q_OBJECT

public:
    explicit DialogExample1(QWidget *parent = 0);
    ~DialogExample1();

private:
    Ui::DialogExample1 *ui;

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
};

#endif // DIALOGEXAMPLE1_H
