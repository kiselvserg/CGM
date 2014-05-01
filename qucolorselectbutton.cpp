#include "qucolorselectbutton.h"

QUColorSelectButton::QUColorSelectButton( const QString& text, QWidget* parent )
: QToolButton( parent )
{
    if( !text.isEmpty() )
    {
        setToolButtonStyle( Qt::ToolButtonTextBesideIcon );
        setText( text );
    }

    icon_pix_ = QPixmap( minimumSize().expandedTo( QSize( 22, 22 ) ) - QSize( 8, 8 ) );
    setColor( color_ );

    setPopupMode( InstantPopup );
    QMenu* menu = new QMenu();
    setMenu( menu );

    QTableView* v = new QTableView( menu );
    QStandardItemModel* m = new QStandardItemModel( this );
    m->setColumnCount( 8 );
    m->setRowCount( 6 );

    int row = 0, col = 0;
    for( int g = 0; g < 4; g++ )
        for( int r = 0;  r < 4; r++ )
            for( int b = 0; b < 3; b++ )
            {
                QColor clr( r * 255 / 3, g * 255 / 3, b * 255 / 2 );
                m->setData( m->index( row, col ), QVariant( clr ), Qt::BackgroundRole );
                if( row == 5 )
                    row = 0, col++;
                else
                    row++;
            }
    v->setModel( m );

    for( int i = 0; i < 8; i++ )
        v->setColumnWidth( i, cell_width_ );
    for( int i = 0; i < 6; i++ )
        v->setRowHeight( i, cell_width_ );
    v->setSelectionMode( QAbstractItemView::NoSelection );
    v->setEditTriggers( QAbstractItemView::NoEditTriggers );
    v->setFrameStyle( QFrame::NoFrame );
    v->horizontalHeader()->hide();
    v->verticalHeader()->hide();
    v->setFixedSize( cell_width_ * 8, cell_width_ * 6 );
    connect( v, SIGNAL( clicked(QModelIndex) ),
        this, SLOT( selectItemColor(QModelIndex) ) );
    connect( v, SIGNAL( activated(QModelIndex) ),
        this, SLOT( selectItemColor(QModelIndex) ) );

    QWidgetAction* wa = new QWidgetAction( menu );
    wa->setDefaultWidget( v );
    menu->addAction( wa );

    wa = new QWidgetAction( menu );
    QToolButton* tb = new QToolButton( menu );
    tb->setText( tr( "Other Color..." ) );
    tb->setAutoRaise( true );
    connect( tb, SIGNAL( clicked() ), this, SLOT( selectOtherColor() ) );
    wa->setDefaultWidget( tb );
    menu->addAction( wa );
}

void QUColorSelectButton::selectOtherColor()
{
    QColor clr = QColorDialog::getColor( color_ );
    if( clr.isValid() )
    {
        setColor( clr );
        emit colorChanged( clr );
    }
}

void QUColorSelectButton::selectItemColor( const QModelIndex& idx )
{
    QColor clr = idx.data( Qt::BackgroundRole ).value< QColor >();
    setColor( clr );
    emit colorChanged( clr );
    menu()->hide();
}

QColor QUColorSelectButton::color() const
{
    return color_;
}

void QUColorSelectButton::setColor( const QColor& clr )
{
    color_ = clr;
    QPainter p( &icon_pix_ );
    p.setBrush( QBrush( clr ) );
    p.setRenderHint( QPainter::Antialiasing );
    p.drawRect( icon_pix_.rect() );
    setIcon( QIcon( icon_pix_ ) );
}
