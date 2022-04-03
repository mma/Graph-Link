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
    QPointF beginPos = startSlot->GetAnchor();
    QPointF endPos = endSlot->GetAnchor();
    QPainterPath path;
    path.moveTo(beginPos);
    qreal dy = endPos.y() - beginPos.y();
    if (dy < 0)
    {
        dy = -dy;
    }
    if (dy > 60)
    {
        dy = 60;
    }
    QPointF offset(0.0f, dy);
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
