#ifndef MULTIANIMATION_H
#define MULTIANIMATION_H

#include <QDialog>

namespace Ui {
class MultiAnimation;
}

class MultiAnimation : public QDialog
{
    Q_OBJECT

public:
    explicit MultiAnimation(QWidget *parent = 0);
    ~MultiAnimation();

private:
    Ui::MultiAnimation *ui;
};

#endif // MULTIANIMATION_H
