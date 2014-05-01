#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "scene.h"
//#include "qucolorselectbutton.h"
#include "mygroupbox.h"

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
    void clippingPlaneDataSelected(QString, QColor, int);

    void on_drawButton_clicked();

private:
    Ui::MainWindow *ui;
    Scene* scene;
    QVector<QRadioButton*> radiobuttons;
    QUColorSelectButton *colorSelectButton;
    MyGroupBox *alphaBox, *betaBox, *gammaBox;
    QString plane;
    double equals;
    double alpha, beta, gamma;
    QColor currentColor;
};

#endif // MAINWINDOW_H
