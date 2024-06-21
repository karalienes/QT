#ifndef ANIMATION_H
#define ANIMATION_H

#include <QDialog>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>

namespace Ui {
class Animation;
}

class Animation : public QDialog
{
    Q_OBJECT

public:
    explicit Animation(QWidget *parent = 0);
    ~Animation();
    void PushButtonSet();
    void CurveSet();
    void GroupSet();
    void seqGroupSet();

private:
    Ui::Animation *ui;
    QPropertyAnimation *animation;
    QPropertyAnimation *animation2;
    QPropertyAnimation *animation3;
    QParallelAnimationGroup *group;

    QSequentialAnimationGroup *seqgroup;

};

#endif // ANIMATION_H
