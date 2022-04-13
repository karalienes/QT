#ifndef ANIMATION_H
#define ANIMATION_H

#include <QDialog>

namespace Ui {
class Animation;
}

class Animation : public QDialog
{
    Q_OBJECT

public:
    explicit Animation(QWidget *parent = 0);
    ~Animation();

private:
    Ui::Animation *ui;
};

#endif // ANIMATION_H
