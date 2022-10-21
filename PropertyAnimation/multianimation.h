#ifndef MULTIANIMATION_H
#define MULTIANIMATION_H

#include <QDialog>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>

namespace Ui {
class MultiAnimation;
}

class MultiAnimation : public QDialog
{
    Q_OBJECT

public:
    explicit MultiAnimation(QWidget *parent = 0);
    ~MultiAnimation();
    void PushButtonSet();
    void CurveSet();
    void GroupSet();
    void seqGroupSet();

private:
    Ui::MultiAnimation *ui;

    QPropertyAnimation *animation;
    QPropertyAnimation *animation2;
    QPropertyAnimation *animation3;
    QPropertyAnimation *animation4;
    QPropertyAnimation *animation5;
    QPropertyAnimation *animation6;

    QParallelAnimationGroup *group;
    QParallelAnimationGroup *group2;

    QSequentialAnimationGroup *seqgroup;
};

#endif // MULTIANIMATION_H
