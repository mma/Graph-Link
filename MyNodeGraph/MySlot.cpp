#include "MySlot.h"
#include <QPainter>
#include <QDebug>
MySlot::MySlot(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
//    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

QPointF MySlot::GetAnchor()
{
    QPointF endPos = mapToScene(boundingRect().center());
    return endPos;
}

QRectF MySlot::boundingRect() const
{
    return QRectF(0, 0, 2, 2);
}

void MySlot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->setRenderHint(QPainter::Antialiasing);
//    painter->drawRoundedRect(boundingRect(), 5, 5);
}
