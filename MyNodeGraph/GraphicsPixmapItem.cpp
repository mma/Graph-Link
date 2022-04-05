#include "GraphicsPixmapItem.h"
#include <QPixmap>

GraphicsPixmapItem::GraphicsPixmapItem(QGraphicsLayoutItem *parent, bool isLayout) : BaseLayoutItem(parent, isLayout)
{
//    if (!isLayout) {
////        setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
//        setFlag(QGraphicsItem::ItemIsMovable);
//    }


    // 如果设置可选中，那么鼠标事件会被拦截，不会传递到proxywidget，如果这个item放在了proxywidget里
//    setFlag(QGraphicsItem::ItemIsSelectable);


    mItem = std::make_shared<QGraphicsPixmapItem>();
    mItem->setParentItem(this);
    QPixmap p(":/1.jpeg");
    p = p.scaledToWidth(150);
    mItem->setPixmap(p);
    mOut = std::make_shared<MySlot>(this);
}

GraphicsPixmapItem::~GraphicsPixmapItem()
{

}

QRectF GraphicsPixmapItem::boundingRect() const
{
//    return BaseLayoutItem::boundingRect();
    if (isVisible()) {
    return QRectF(0, 0, mItem->boundingRect().width(), mItem->boundingRect().height());
    } else {
        return QRectF();
    }
}

void GraphicsPixmapItem::setGeometry(const QRectF &rect)
{
    BaseLayoutItem::setGeometry(rect);
    mOut->setPos(rect.width() / 2, rect.height());
}
