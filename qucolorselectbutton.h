#ifndef QUCOLORSELECTBUTTON_H
#define QUCOLORSELECTBUTTON_H

#include <QToolButton>
#include <QMenu>
#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QWidgetAction>
#include <QPainter>
#include <QColorDialog>

class QUColorSelectButton: public QToolButton
{
    Q_OBJECT
public:
    QUColorSelectButton( const QString& text, QWidget* parent = 0 );

    QColor color() const;
    void setColor( const QColor& clr );

Q_SIGNALS:
    void colorChanged( const QColor& );

protected Q_SLOTS:
    void selectOtherColor();
    void selectItemColor( const QModelIndex& idx );

private:
    QColor color_;
    QPixmap	icon_pix_;
    static const int cell_width_ = 16;
};

#endif // QUCOLORSELECTBUTTON_H
