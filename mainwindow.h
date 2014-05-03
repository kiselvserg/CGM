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
    void on_clearAllButton_clicked();
    void on_undoButton_clicked();
    void updateSlider(int);

private:
    Ui::MainWindow *ui;
    Scene* scene_;
    QVector<QRadioButton*> radiobuttons_;
    QUColorSelectButton *colorSelectButton_;
    MyGroupBox *alphaBox_, *betaBox_, *gammaBox_;
    QString plane_;
    double equals_;
    double alpha_, beta_, gamma_;
    QColor currentColor_;
};

#endif // MAINWINDOW_H
