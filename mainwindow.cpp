#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), plane(QString()), equals(0), alpha(0), beta(0), gamma(0), currentColor(QColor())
{
    ui->setupUi(this);
    scene = new Scene();
    ui->sceneLayout->addWidget(scene);
    ui->horizontalSlider->setMaximum(0);
    alpha = 3.0/ui->alphaSpinBox->value();
    beta = 2.0/ui->betaSpinBox->value();
    gamma = 11.0/ui->gammaSpinBox->value();

    QVector<QString> alpha_coef; alpha_coef << "111";
    QVector<QString> beta_coef; beta_coef << "110" << "101" << "011";
    QVector<QString> gamma_coef; gamma_coef << "113" << "131" << "311";

    alphaBox = new MyGroupBox(alpha_coef, "alpha depended", 1, this);
    betaBox = new MyGroupBox(beta_coef, "beta depended", 2, this);
    gammaBox = new MyGroupBox(gamma_coef, "gamma depended", 3, this);

    ui->millerIndecies->addWidget(alphaBox);
    ui->millerIndecies->addWidget(betaBox);
    ui->millerIndecies->addWidget(gammaBox);

    connect(alphaBox, SIGNAL(radioButtonSelected(QString,QColor,int)), this, SLOT(clippingPlaneDataSelected(QString,QColor,int)));
    connect(betaBox, SIGNAL(radioButtonSelected(QString,QColor,int)), this, SLOT(clippingPlaneDataSelected(QString,QColor,int)));
    connect(gammaBox, SIGNAL(radioButtonSelected(QString,QColor,int)), this, SLOT(clippingPlaneDataSelected(QString,QColor,int)));

    connect(scene, SIGNAL(clipChanged(int)), this, SLOT(updateSlider(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), scene, SLOT(showScene(int)));
}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
}

void MainWindow::on_alphaSpinBox_valueChanged(double arg1)
{
    alpha = arg1;
    equals = 3.0/(alpha);
}

void MainWindow::on_betaSpinBox_valueChanged(double arg1)
{
    beta = arg1;
    equals = 2.0/(beta);
}

void MainWindow::on_gammaSpinBox_valueChanged(double arg1)
{
    gamma = arg1;
    equals = 11.0/(gamma);
}

void MainWindow::clippingPlaneDataSelected(QString str, QColor col, int i)
{
    switch(i)
    {
    case 1:
        ui->alphaSpinBox->setEnabled(1);
        ui->betaSpinBox->setEnabled(0);
        ui->gammaSpinBox->setEnabled(0);
        betaBox->unSelect();
        gammaBox->unSelect();
        equals = 3.0 / ui->alphaSpinBox->value();
        break;
    case 2:
        ui->alphaSpinBox->setEnabled(0);
        ui->betaSpinBox->setEnabled(1);
        ui->gammaSpinBox->setEnabled(0);
        equals = 2.0/ui->betaSpinBox->value();
        alphaBox->unSelect();
        gammaBox->unSelect();
        break;
    case 3:
        ui->alphaSpinBox->setEnabled(0);
        ui->betaSpinBox->setEnabled(0);
        ui->gammaSpinBox->setEnabled(1);
        equals = 11.0/ui->gammaSpinBox->value();
        betaBox->unSelect();
        alphaBox->unSelect();
        break;
    }
    plane = str;
    currentColor = col;
}

void MainWindow::on_drawButton_clicked()
{
    array<int, 3> value = {plane[0].digitValue(), plane[1].digitValue(), plane[2].digitValue()};
    scene->clipping(value, equals, currentColor);
    if(ui->label->text().isEmpty()) { ui->label->setText(tr("<font color = '%1'>{%2}</font>").arg(currentColor.name()).arg(plane)); return; }
    ui->label->setText(ui->label->text() + tr(" + <font color = '%1'>{%2}</font>").arg(currentColor.name()).arg(plane));
}

void MainWindow::on_clearAllButton_clicked()
{
    scene->clearAll();
}

void MainWindow::on_undoButton_clicked()
{
    scene->undo();
    QStringList list = ui->label->text().split("+");
    list.removeLast();
    ui->label->clear();
    for(auto i : list) ui->label->setText(ui->label->text() + i);
}

void MainWindow::updateSlider(int value)
{
    ui->horizontalSlider->setMaximum(value);
    ui->horizontalSlider->setValue(value);
}
