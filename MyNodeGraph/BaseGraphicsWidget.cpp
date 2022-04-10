﻿#include "BaseGraphicsWidget.h"
#include <QPainter>
#include <QGraphicsLayout>

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
    QGraphicsWidget::paint(painter,option,widget);
}

// 重置每个Layout的size大小
void BaseGraphicsWidget::Invalidate()
{
    Invalidate(layout());
}

// 重置每个Layout的size大小, 并且让Layout重新计算合适的大小,让widget更新大小
void BaseGraphicsWidget::UpdateLayout()
{
    Invalidate();
    adjustSize();
    // adjustedSize() => QSizeF sz = effectiveSizeHint(Qt::SizeHint::PreferredSize); if (sz.isValid()) resize(sz);
}

void BaseGraphicsWidget::Invalidate(QGraphicsLayout *l)
{
    l->invalidate();
    for (int i = 0; i < l->count(); ++i) {
        QGraphicsLayoutItem *item = l->itemAt(i);
        if (item->isLayout()) {
            Invalidate(static_cast<QGraphicsLayout *>(item));
        }
    }
}
