#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void propertyAnimation();

private slots:
    void on_Timer_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_StatePush_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
