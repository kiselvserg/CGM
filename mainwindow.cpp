#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new Scene();
    ui->sceneLayout->addWidget(scene);
    scene->setAlpha(ui->alphaSpinBox->value());
    scene->setBeta(ui->betaSpinBox->value());
    scene->setGamma(ui->gammaSpinBox->value());
    ui->tabWidget->setStyleSheet(tr("background-color: ") + this->palette().color(QPalette::Window).name());

    //colorSelectButton = new QUColorSelectButton("", this);
    //ui->verticalLayout_3->addWidget(colorSelectButton);
    //colorSelectButton->setColor(QColor("#13456f"));

    scene->updateGL();
}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
}

void MainWindow::on_alphaSpinBox_valueChanged(double arg1)
{
    scene->setAlpha(arg1);
    scene->updateGL();
}

void MainWindow::on_betaSpinBox_valueChanged(double arg1)
{
    scene->setBeta(arg1);
    scene->updateGL();
}

void MainWindow::on_gammaSpinBox_valueChanged(double arg1)
{
    scene->setGamma(arg1);
    scene->updateGL();
}
