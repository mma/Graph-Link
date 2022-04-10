﻿#ifndef GRAPHICSPIXMAPITEM_H
#define GRAPHICSPIXMAPITEM_H
#include "BaseLayoutItem.h"
#include "MySlot.h"

class GraphicsPixmapItem : public BaseLayoutItem
{
    Q_OBJECT
public:
    GraphicsPixmapItem(QGraphicsLayoutItem *parent = nullptr, bool isLayout = false);
    ~GraphicsPixmapItem();
    MySlot *GetSlot() { return mOut.get(); }
    virtual QRectF boundingRect()const override;
    virtual void setGeometry(const QRectF &rect)override;
    QVariant itemChange(GraphicsItemChange change, const QVariant& value)override;

private:
    std::shared_ptr<QGraphicsPixmapItem> mItem;
    std::shared_ptr<MySlot> mOut;
};

#endif // GRAPHICSPIXMAPITEM_H
