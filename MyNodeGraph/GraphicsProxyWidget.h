#ifndef GRAPHICSPROXYWIDGET_H
#define GRAPHICSPROXYWIDGET_H

#include <QGraphicsProxyWidget>

class GraphicsProxyWidget : public QGraphicsProxyWidget
{
    Q_OBJECT
public:
    GraphicsProxyWidget(QGraphicsItem *parent = nullptr);
    void setCenterWidget(QWidget * w);
    void setCenterLayout(QGraphicsLayout * layout);
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value)override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override;
    virtual QRectF boundingRect()const override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event)override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event)override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)override;
private:
    QSizeF itemSize;
    QSizeF itemMinSize;
    bool IsInResizeArea(const QPointF& pos);
    bool isResizing;
    QPointF dragPosition;
    bool grabbedByWidget;
};

#endif // GRAPHICSPROXYWIDGET_H
