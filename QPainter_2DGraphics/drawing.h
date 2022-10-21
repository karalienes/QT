#ifndef DRAWING_H
#define DRAWING_H

#include <QDialog>
#include <QPainter>

namespace Ui {
class Drawing;
}

class Drawing : public QDialog
{
    Q_OBJECT

public:
    explicit Drawing(QWidget *parent = 0);
    ~Drawing();
    virtual void paintEvent(QPaintEvent *event);


private:
    Ui::Drawing *ui;
};

#endif // DRAWING_H
