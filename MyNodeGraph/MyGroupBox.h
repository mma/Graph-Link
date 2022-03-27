#ifndef MYGROUPBOX_H
#define MYGROUPBOX_H
#include <QGraphicsRectItem>

class MyGroupBox : public QGraphicsItem
{
public:
    MyGroupBox(QGraphicsItem *parent = nullptr);
    void AddItem(QGraphicsItem *item);
    QVector<QGraphicsItem *> items;
protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void Layout();
private:
    QRect mm;
};

#endif // MYGROUPBOX_H
