#ifndef YOURAGE_H
#define YOURAGE_H

#include <QDialog>
#include <QApplication>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>


namespace Ui {
class YourAge;
}

class YourAge : public QDialog
{
    Q_OBJECT

public:
    explicit YourAge(QWidget *parent = 0);
    ~YourAge();
    void YourAgeFunc();


private:
    Ui::YourAge *ui;
};

#endif // YOURAGE_H
