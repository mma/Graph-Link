#include "BaseGraphicsWidget.h"
#include <QPainter>

BaseGraphicsWidget::BaseGraphicsWidget(QGraphicsItem *parent, Qt::WindowFlags wFlags) : QGraphicsWidget(parent, wFlags)
{
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);//图形项可发送位置变化信号
//    setFlag(QGraphicsItem::ItemIsSelectable);
//    setFlag(QGraphicsItem::ItemIsFocusable);
    setContentsMargins(0, 0, 0, 0);
}

BaseGraphicsWidget::~BaseGraphicsWidget()
{

}

QVariant BaseGraphicsWidget::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    return QGraphicsWidget::itemChange(change, value);
}

QRectF BaseGraphicsWidget::boundingRect() const
{
    return QGraphicsWidget::boundingRect();
}

void BaseGraphicsWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing,true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform,true);
    painter->setRenderHint(QPainter::TextAntialiasing,true);
    painter->drawRect(rect());

    painter->restore();
    QGraphicsWidget::paint(painter,option,widget);
}
