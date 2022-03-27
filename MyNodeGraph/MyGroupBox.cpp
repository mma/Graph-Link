#include "MyGroupBox.h"
#include <QPainter>
#include <BaseItem.h>
#include <QStyleOptionGraphicsItem>

MyGroupBox::MyGroupBox(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    mm = QRect(0, 0, 200, 200);
}

void MyGroupBox::AddItem(QGraphicsItem *item)
{
    // 上100 左100 margin 40
    QRectF rc = item->boundingRect();
    mm.setWidth(mm.width() + rc.width());
    if (items.size() != 0) {
        mm.setWidth(mm.width() + 40);
    }
    mm.setHeight(200 + rc.height());
    item->setFlag(QGraphicsItem::ItemIsMovable, false);
    item->setParentItem(this);
//    item->setPos(100, 100);
    item->setZValue(zValue() + 1);
    items.push_back(item);
//    update();
    Layout();
}

QRectF MyGroupBox::boundingRect() const
{
    return mm;
}

void MyGroupBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->fillRect(boundingRect(), Qt::gray);
    painter->save();
    if (option->state.testFlag(QStyle::State_Selected)) {
        QPen pen = painter->pen();
        pen.setStyle(Qt::DotLine);
        painter->setPen(pen);
    }
    painter->drawRect(boundingRect());
    painter->restore();
}

void MyGroupBox::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    for (int i = 0; i < items.size(); ++i) {
        static_cast<BaseItem *>(items[i])->Update();
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void MyGroupBox::Layout()
{
    int www = 0;
    for (int i = 0; i < items.size(); ++i) {
        int w = items[i]->boundingRect().width();
        int h = items[i]->boundingRect().height();
        items[i]->setPos(100 + www, 100);
        www += w + 40;
    }
}
