#include "GraphicsPixmapTitleItem.h"
#include <QDebug>
GraphicsPixmapTitleItem::GraphicsPixmapTitleItem(QGraphicsLayoutItem *parent, bool is) : BaseLayoutItem(parent, is)
{
    mItem = std::make_shared<QGraphicsSimpleTextItem>();
    mItem->setParentItem(this);
    mItem->setText("This is a simple demo!!!");
    mIn = std::make_shared<MySlot>(this);
}

GraphicsPixmapTitleItem::~GraphicsPixmapTitleItem()
{

}

QRectF GraphicsPixmapTitleItem::boundingRect() const
{
//    return BaseLayoutItem::boundingRect();
    if (isVisible()) {
    return QRectF(0, 0, mItem->boundingRect().width(), mItem->boundingRect().height());
    } else {
        return QRectF();
    }
}

void GraphicsPixmapTitleItem::setGeometry(const QRectF &rect)
{
    BaseLayoutItem::setGeometry(rect);
    mIn->setPos(rect.width() / 2, 0);
}
