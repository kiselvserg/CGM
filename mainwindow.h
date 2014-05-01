#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "scene.h"
#include "qucolorselectbutton.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_alphaSpinBox_valueChanged(double arg1);
    void on_betaSpinBox_valueChanged(double arg1);
    void on_gammaSpinBox_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
    Scene* scene;
    QUColorSelectButton *colorSelectButton;
};

#endif // MAINWINDOW_H
