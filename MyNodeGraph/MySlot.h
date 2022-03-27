#ifndef MYSLOT_H
#define MYSLOT_H
#include <QGraphicsRectItem>
#include <QObject>

class MySlot : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    MySlot(QGraphicsItem *parent = nullptr);
    QPointF GetAnchor();

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

};

#endif // MYSLOT_H
