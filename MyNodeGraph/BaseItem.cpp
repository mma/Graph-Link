#include "BaseItem.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
#include <MyScene.h>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGraphicsProxyWidget>

BaseItem::BaseItem(Direction dir, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    d = dir;
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    s1 = new MySlot(this);
    pi = new QGraphicsPixmapItem(this);
    QPixmap p(":/1.jpeg");
    p = p.scaledToWidth(100);
    pi->setPixmap(p);
    //    QWidget *w = new QWidget();
//    QVBoxLayout *l = new QVBoxLayout();
//    w->setLayout(l);
//    QPushButton *b = new QPushButton("xxx");
//    l->addWidget(b);
//    gw = new QGraphicsProxyWidget(this);
//    gw->setWidget(w);
}

BaseItem::~BaseItem()
{
    delete s1;
}

void BaseItem::Update()
{
    qobject_cast<MyScene *>(scene())->Update();
}

QPainterPath BaseItem::shape() const
{
    QPainterPath pp;
    pp.addRect(boundingRect());
    return pp;
}

QRectF BaseItem::boundingRect() const
{
    if (d == UP) {
        s1->setPos(100 - 5, 0 - 5);
    } else if (d == LEFT) {
        s1->setPos(0 - 5, 50 - 5);
    } else if (d == RIGHT) {
        s1->setPos(200 - 5, 50 - 5);
    } else {
        s1->setPos(100 - 5, 100 - 5);
    }
    pi->setPos(50, 0);
//    gw->setGeometry(QRectF(10, 10, 200 - 20, 100 - 20));
    return QRectF(0, 0, 200, 100);
}

void BaseItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing,true);
//    painter->fillRect(boundingRect(), Qt::green);
    painter->save();
    if (option->state.testFlag(QStyle::State_Selected)) {
        QPen pen = painter->pen();
        pen.setStyle(Qt::DashDotLine);
        painter->setPen(pen);
    }
    painter->drawRect(boundingRect());
    painter->restore();
}

void BaseItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Update();
    QGraphicsItem::mouseMoveEvent(event);
}
