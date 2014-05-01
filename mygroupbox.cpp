#include "mygroupbox.h"

MyGroupBox::MyGroupBox(const QVector<QString>& labels, const QString& title, int type, QWidget *parent) :
    QGroupBox(title, parent), labels_(labels), type_(type), size(labels.size())
{
    layout = new QFormLayout();
    radio.resize(size+1);
    colorSelections.resize(size+1);
    for(int i = 0; i < size; i++)
    {
        radio[i] = new QRadioButton(labels[i], this);
        colorSelections[i] = new QUColorSelectButton("", this);
        layout->addRow(radio[i], colorSelections[i]);
        connect(radio[i], SIGNAL(clicked()), this, SLOT(radioSelected()));
        connect(colorSelections[i], SIGNAL(colorChanged(QColor)), this, SLOT(colorChanged(QColor)));
    }
    this->setLayout(layout);
}

void MyGroupBox::unSelect()
{
    for(int i = 0; i < size; i++)
    {
        radio[i]->setAutoExclusive(false);
        radio[i]->setChecked(false);
        radio[i]->setAutoExclusive(true);
    }
}

void MyGroupBox::radioSelected()
{
    for(int i = 0; i <size; i++)
        if(radio[i]->isChecked())
        {
            emit radioButtonSelected(radio[i]->text(), colorSelections[i]->color(), type_);
        }
}

void MyGroupBox::colorChanged(QColor)
{
    radioSelected();
}
