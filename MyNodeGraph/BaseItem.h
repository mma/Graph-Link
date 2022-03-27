#ifndef BASEITEM_H
#define BASEITEM_H
#include <QGraphicsItem>
#include <QObject>
#include "MySlot.h"
class QGraphicsProxyWidget;
class BaseItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum Direction {
        UP,
        LEFT,
        RIGHT,
        DOWN
    };
    BaseItem(Direction dir = RIGHT, QGraphicsItem *parent = nullptr);
    ~BaseItem();
    MySlot *GetSlot() {return s1; }

    void Update();
protected:
    QPainterPath shape() const override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    MySlot *s1;
    QGraphicsProxyWidget *gw;
    QGraphicsPixmapItem *pi;
    Direction d;
};

#endif // BASEITEM_H
