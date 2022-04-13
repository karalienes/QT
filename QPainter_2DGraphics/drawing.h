#ifndef DRAWING_H
#define DRAWING_H

#include <QDialog>

namespace Ui {
class Drawing;
}

class Drawing : public QDialog
{
    Q_OBJECT

public:
    explicit Drawing(QWidget *parent = 0);
    ~Drawing();

private:
    Ui::Drawing *ui;
};

#endif // DRAWING_H
