#include "mygroupbox.h"

MyGroupBox::MyGroupBox(const QVector<QString>& labels, const QString& title, int type, QWidget *parent) :
    QGroupBox(title, parent), labels_(labels), type_(type)
{
    layout = new QFormLayout();
    radio.resize(labels.size()+1);
    colorSelections.resize(labels.size()+1);
    //color.resize(labels.size()+1);
    for(int i = 0; i < labels.size(); i++)
    {
        radio[i] = new QRadioButton(labels[i], this);
        colorSelections[i] = new QUColorSelectButton("", this);
        layout->addRow(radio[i], colorSelections[i]);
        connect(radio[i], SIGNAL(clicked()), this, SLOT(radioSelected()));
        connect(colorSelections[i], SIGNAL(colorChanged(QColor)), this, SLOT(colorChanged(QColor)));
    }
    this->setLayout(layout);
}

bool MyGroupBox::selected(radioValue* v)
{

    for(int i = 0; i < labels_.size(); i++)
        if(radio[i]->isChecked())
        {
            v->text = radio[i]->text();
            v->color = colorSelections[i]->color();
            return true;
        }
    return false;
}

void MyGroupBox::radioSelected()
{
    for(int i = 0; i < labels_.size(); i++)
        if(radio[i]->isChecked())
        {
            emit radioButtonSelected(radio[i]->text(), colorSelections[i]->color(), type_);
        }
}

void MyGroupBox::colorChanged(QColor)
{
    radioSelected();
}
