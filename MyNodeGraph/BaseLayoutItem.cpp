#include "BaseLayoutItem.h"
#include <QWidget>
#include <QDebug>

BaseLayoutItem::BaseLayoutItem(QGraphicsLayoutItem *parent, bool isLayout) : QGraphicsLayoutItem(parent, isLayout),
    mItemSize(250, 250)
{
    setGraphicsItem(this);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);//图形项可发送位置变化信号
}

BaseLayoutItem::~BaseLayoutItem()
{

}

QRectF BaseLayoutItem::boundingRect() const
{
    return  QRectF(0, 0, mItemSize.width(), mItemSize.height());
}

void BaseLayoutItem::setGeometry(const QRectF &rect)
{
    prepareGeometryChange();
    QGraphicsLayoutItem::setGeometry(rect);
    setPos(rect.topLeft());

    QSizeF effectiveSize = rect.size().expandedTo(effectiveSizeHint(Qt::MinimumSize))
                                .boundedTo(effectiveSizeHint(Qt::MaximumSize));
    mItemSize = QRectF(rect.topLeft(), effectiveSize).size();
}

void BaseLayoutItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QSizeF BaseLayoutItem::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
//    auto p = parentItem()->toGraphicsObject();
//    qDebug()<<p->metaObject()->className()<<which;

    switch ( which )
    {
        case Qt::MinimumSize:
        return QSizeF(0, 0);
        case Qt::PreferredSize:
            return this->boundingRect().size();
        case Qt::MaximumSize:
            return QSizeF(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
        default:
            return this->boundingRect().size();
    }
    return constraint;
}
