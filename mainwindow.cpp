#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), plane_(QString()), equals_(0), alpha_(0), beta_(0), gamma_(0), currentColor_(QColor())
{
    ui->setupUi(this);
    scene_ = new Scene();
    ui->sceneLayout->addWidget(scene_);
    ui->horizontalSlider->setMaximum(0);
    alpha_ = 3.0/ui->alphaSpinBox->value();
    beta_ = 2.0/ui->betaSpinBox->value();
    gamma_ = 11.0/ui->gammaSpinBox->value();

    QVector<QString> alpha_coef; alpha_coef << "111";
    QVector<QString> beta_coef; beta_coef << "110" << "101" << "011";
    QVector<QString> gamma_coef; gamma_coef << "113" << "131" << "311";

    alphaBox_ = new MyGroupBox(alpha_coef, "alpha depended", 1, this);
    betaBox_ = new MyGroupBox(beta_coef, "beta depended", 2, this);
    gammaBox_ = new MyGroupBox(gamma_coef, "gamma depended", 3, this);

    ui->millerIndecies->addWidget(alphaBox_);
    ui->millerIndecies->addWidget(betaBox_);
    ui->millerIndecies->addWidget(gammaBox_);

    ui->undoButton->setEnabled(false);
    ui->clearAllButton->setEnabled(false);
    ui->drawButton->setEnabled(false);

    connect(alphaBox_, SIGNAL(radioButtonSelected(QString,QColor,int)), this, SLOT(clippingPlaneDataSelected(QString,QColor,int)));
    connect(betaBox_, SIGNAL(radioButtonSelected(QString,QColor,int)), this, SLOT(clippingPlaneDataSelected(QString,QColor,int)));
    connect(gammaBox_, SIGNAL(radioButtonSelected(QString,QColor,int)), this, SLOT(clippingPlaneDataSelected(QString,QColor,int)));

    connect(scene_, SIGNAL(clipChanged(int)), this, SLOT(updateSlider(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), scene_, SLOT(showScene(int)));
}

MainWindow::~MainWindow()
{
    delete scene_;
    delete ui;
}

void MainWindow::on_alphaSpinBox_valueChanged(double arg1)
{
    alpha_ = arg1;
    equals_ = 3.0/(alpha_);
}

void MainWindow::on_betaSpinBox_valueChanged(double arg1)
{
    beta_ = arg1;
    equals_ = 2.0/(beta_);
}

void MainWindow::on_gammaSpinBox_valueChanged(double arg1)
{
    gamma_ = arg1;
    equals_ = 11.0/(gamma_);
}

void MainWindow::clippingPlaneDataSelected(QString str, QColor color, int i)
{
    ui->drawButton->setEnabled(true);
    switch(i)
    {
    case 1:
        ui->alphaSpinBox->setEnabled(1);
        ui->betaSpinBox->setEnabled(0);
        ui->gammaSpinBox->setEnabled(0);
        betaBox_->unSelect();
        gammaBox_->unSelect();
        equals_ = 3.0 / ui->alphaSpinBox->value();
        break;
    case 2:
        ui->alphaSpinBox->setEnabled(0);
        ui->betaSpinBox->setEnabled(1);
        ui->gammaSpinBox->setEnabled(0);
        equals_ = 2.0/ui->betaSpinBox->value();
        alphaBox_->unSelect();
        gammaBox_->unSelect();
        break;
    case 3:
        ui->alphaSpinBox->setEnabled(0);
        ui->betaSpinBox->setEnabled(0);
        ui->gammaSpinBox->setEnabled(1);
        equals_ = 11.0/ui->gammaSpinBox->value();
        betaBox_->unSelect();
        alphaBox_->unSelect();
        break;
    }
    plane_ = str;
    currentColor_ = color;
}

void MainWindow::on_drawButton_clicked()
{
    ui->undoButton->setEnabled(true);
    ui->clearAllButton->setEnabled(true);
    array<int, 3> value = {plane_[0].digitValue(), plane_[1].digitValue(), plane_[2].digitValue()};
    scene_->clipping(value, equals_, currentColor_);
    if(ui->label->text().isEmpty()) { ui->label->setText(tr("<font color = '%1'>{%2}</font>").arg(currentColor_.name()).arg(plane_)); return; }
    ui->label->setText(ui->label->text() + tr(" + <font color = '%1'>{%2}</font>").arg(currentColor_.name()).arg(plane_));
}

void MainWindow::on_clearAllButton_clicked()
{
    scene_->clearAll();
    ui->label->clear();
}

void MainWindow::on_undoButton_clicked()
{
    scene_->undo();
    QStringList list = ui->label->text().split("+");
    list.removeLast();
    ui->label->clear();
    if(list.isEmpty()) { return; }
    ui->label->setText(list.first());
    for(int i = 1; i < list.size(); i++) ui->label->setText(ui->label->text() + " + " + list[i]);
}

void MainWindow::updateSlider(int value)
{
    if(value == 0 ) { ui->undoButton->setEnabled(false); ui->clearAllButton->setEnabled(false); }
    ui->horizontalSlider->setMaximum(value);
    ui->horizontalSlider->setValue(value);
}
