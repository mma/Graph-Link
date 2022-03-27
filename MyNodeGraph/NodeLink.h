#ifndef NODELINK_H
#define NODELINK_H
#include "MySlot.h"
#include <QGraphicsPathItem>

class NodeLink : public QGraphicsPathItem
{
public:
    NodeLink(MySlot *s1, MySlot *s2);
    ~NodeLink();
    void updateShape();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QPainterPath shape() const override;

private:
    MySlot *startSlot;
    MySlot *endSlot;
};

#endif // NODELINK_H
