#include "BaseLayoutItem.h"
#include "BaseItem.h"
#include <QWidget>

BaseLayoutItem::BaseLayoutItem(QGraphicsLayoutItem *parent, bool isLayout) : QGraphicsLayoutItem(parent, isLayout)
{
    BaseItem *b = new BaseItem();
    setGraphicsItem(b);
}

BaseLayoutItem::~BaseLayoutItem()
{

}

QSizeF BaseLayoutItem::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint);
    QSizeF sh;
    switch (which) {
        case Qt::MinimumSize:
            sh = QSizeF(0, 0);
            break;
        case Qt::PreferredSize:
            sh = QSizeF(50, 50);
            break;
        case Qt::MaximumSize:
            sh = QSizeF(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
            break;
        default:
            break;
    }
    return sh;
}
