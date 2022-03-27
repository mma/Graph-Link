#include "NodeLink.h"
#include <QPainter>

NodeLink::NodeLink(MySlot *s1, MySlot *s2) : startSlot(s1), endSlot(s2)
{
    setFlags(QGraphicsItem::ItemIsSelectable);
}

NodeLink::~NodeLink()
{

}

void NodeLink::updateShape()
{
    const QPointF& beginPos = startSlot->GetAnchor();
    QPointF endPos = endSlot->GetAnchor();
    QPainterPath path;
    path.moveTo(beginPos);
    qreal dx = endPos.x() - beginPos.x();
    if (dx < 0)
    {
        dx = -dx;
    }
    if (dx > 60)
    {
        dx = 60;
    }
    QPointF offset(dx, 0.0f);
    path.cubicTo(beginPos + offset, endPos - offset, endPos);
    setPath(path);
    update();
}

void NodeLink::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    QGraphicsPathItem::paint(painter, option, widget);
}

QPainterPath NodeLink::shape() const
{
    QPainterPathStroker s;
    s.setWidth(10);
    return s.createStroke(QGraphicsPathItem::shape());
}
