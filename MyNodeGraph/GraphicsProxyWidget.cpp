#include "graphicsproxywidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsLayout>

const qreal g_cResizePos[] = {9, 6, 3};

GraphicsProxyWidget::GraphicsProxyWidget(QGraphicsItem *parent)
    :QGraphicsProxyWidget(parent)
{
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);//图形项可发送位置变化信号
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsFocusable);
    this->itemSize = QSizeF(100,100);
}

bool GraphicsProxyWidget::IsInResizeArea(const QPointF& pos)
{
    return (pos.x() - itemSize.width() + g_cResizePos[0]) > (itemSize.height() - pos.y());
}

QRectF GraphicsProxyWidget::boundingRect() const
{
    return  QRectF(0, 0, itemSize.width() + 5, itemSize.height() + 5);
}

void GraphicsProxyWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QPointF pos = event->pos();
        if(IsInResizeArea(pos))
        {
            isResizing = true;
        }
        else
        {
            if(widget())
            {
                if (auto alienWidget = widget()->childAt(pos.toPoint()))
                {
                    QGraphicsProxyWidget::mousePressEvent(event);
                    grabbedByWidget = true;
                }
                else
                {
                    QGraphicsItem::mousePressEvent(event);
                    grabbedByWidget = false;
                }
            }
            else
            {
                QGraphicsItem::mousePressEvent(event);
                grabbedByWidget = false;
            }
        }
    }
}

void GraphicsProxyWidget::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if(widget())
    {
        if (auto alienWidget = widget()->childAt(event->pos().toPoint()))
        {
            QGraphicsProxyWidget::mouseDoubleClickEvent(event);
            grabbedByWidget = true;
        }
        else
        {
            QGraphicsItem::mouseDoubleClickEvent(event);
            grabbedByWidget = false;
        }
    }
    else
    {
        QGraphicsItem::mouseDoubleClickEvent(event);
        grabbedByWidget = false;
    }
}

void GraphicsProxyWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && isResizing)
        isResizing = false;
    else
    {
        if (grabbedByWidget)
            QGraphicsProxyWidget::mouseReleaseEvent(event);
        else
            QGraphicsItem::mouseReleaseEvent(event);
    }

    grabbedByWidget = false;
}

QVariant GraphicsProxyWidget::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if ((change == ItemPositionChange || change == ItemPositionHasChanged) && scene()) // 控件发生移动
    {
        QPointF newPos = value.toPointF();
        QRectF rect(0, 0, scene()->width(), scene()->height());
        if (!rect.contains(newPos))//左上角
        {
            newPos.setX(qMin(rect.width(), qMax(newPos.x(), 0.0)));
            newPos.setY(qMin(rect.height(), qMax(newPos.y(), 0.0)));
            return newPos;
        }

        QRectF thisRectF = boundingRect();
        QPointF nowPos = QPointF(newPos.x() + thisRectF.width(),newPos.y());
        if(!rect.contains(nowPos))//右上角
        {
            newPos.setX(rect.width() - thisRectF.width());
            this->setPos(newPos);
            return newPos;
        }

        nowPos = QPointF(newPos.x(),newPos.y() + thisRectF.height());
        if(!rect.contains(nowPos))//左下角
        {
            newPos.setY(rect.height() - thisRectF.height());
            this->setPos(newPos);
            return newPos;
        }
    }
    return QGraphicsItem::itemChange(change, value);
}

void GraphicsProxyWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing,true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform,true);
    painter->setRenderHint(QPainter::TextAntialiasing,true);

    QRectF thisRectF = boundingRect();
    painter->fillRect(option->rect,QBrush(QColor("#e0e0e0")));

    if(option->state & QStyle::State_Selected)
    {
        qreal w = thisRectF.width();
        qreal h = thisRectF.height();
        painter->setPen(Qt::red);
        for (int i = 0; i < 3; ++i)//三角形
            painter->drawLine(static_cast<int>(w - g_cResizePos[i]) , static_cast<int>(h), static_cast<int>(w), static_cast<int>(h - g_cResizePos[i]));
    }

    painter->restore();
    QGraphicsProxyWidget::paint(painter,option,widget);
}

void GraphicsProxyWidget::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
    if (isResizing || (IsInResizeArea(event->pos()) && isSelected()))
    {
        setCursor(Qt::SizeFDiagCursor);
        QGraphicsObject::hoverMoveEvent(event);
    }
    else
    {
        if(widget())
        {
            if (auto alienWidget = widget()->childAt(event->pos().toPoint()))
            {
                setCursor(alienWidget->cursor());
            }
            else
                setCursor(Qt::ArrowCursor);
        }
        else
            setCursor(Qt::ArrowCursor);

        QGraphicsProxyWidget::hoverMoveEvent(event);
    }
}

void GraphicsProxyWidget::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (isResizing)
    {
        qreal w = event->pos().x();
        qreal h = event->pos().y();
        if (w > itemMinSize.width())
            itemSize.setWidth(w);
        if (h > itemMinSize.height())
            itemSize.setHeight(h);
        resize(w,h);
        if(layout())
        {
            layout()->invalidate();
        }
        prepareGeometryChange();
    }
    else
    {
        if (grabbedByWidget)
        {
            QGraphicsProxyWidget::mouseMoveEvent(event);
        }
        else
            QGraphicsItem::mouseMoveEvent(event);
    }
}

void GraphicsProxyWidget::setCenterWidget(QWidget * w)
{
    setWidget(w);
    itemSize = w->sizeHint();
    itemMinSize = w->minimumSize();
    update();
}

void GraphicsProxyWidget::setCenterLayout(QGraphicsLayout * layout)
{
    setLayout(layout);
    setContentsMargins(10,10,10,10);

    adjustSize();
    itemSize = this->sizeHint(Qt::PreferredSize);
    itemMinSize = this->sizeHint(Qt::MinimumDescent);
}

void GraphicsProxyWidget::UpdateGeometry()
{
    layout()->updateGeometry();
    adjustSize();
    itemSize = this->sizeHint(Qt::PreferredSize);
}
