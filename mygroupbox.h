#ifndef MYGROUPBOX_H
#define MYGROUPBOX_H

#include <QGroupBox>
#include <QRadioButton>
#include <QFormLayout>
#include "qucolorselectbutton.h"

struct radioValue
{
    QString text;
    QColor color;
    radioValue(QString t, QColor c) : text(t), color(c) {}
    radioValue() : text(QString()), color(QColor()) {}
};

class MyGroupBox : public QGroupBox
{
    Q_OBJECT
public:
    MyGroupBox(const QVector<QString> &labels, const QString &title, int type, QWidget *parent = 0);
    void unSelect();

Q_SIGNALS:
    void radioButtonSelected(QString, QColor, int);

private slots:
    void radioSelected();
    void colorChanged(QColor);

private:
    QVector<QRadioButton*> radio;
    QVector<QUColorSelectButton*> colorSelections;
    QVector<QString> labels_;
    QFormLayout* layout;
    int type_;
    int size;

};

#endif // MYGROUPBOX_H
