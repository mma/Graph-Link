#ifndef GRAPHICSTEXTANDPIXMAPITEM_H
#define GRAPHICSTEXTANDPIXMAPITEM_H
#include <QGraphicsLinearLayout>
#include "GraphicsPixmapItem.h"
#include "BaseGraphicsWidget.h"
#include "GraphicsPixmapTitleItem.h"
#include "InfosItem.h"

/// 采用QGraphicsLayout布局，但是只能是QGraphicsLayoutItem的子类
/// 所以先用BaseLayoutItem包装一下QGraphicsPixmapItem和QGraphicsSimpleTextItem
/// 然后再在QGraphicsWidget里面组装一下

class GraphicsTextAndPixmapItem : public BaseGraphicsWidget
{
    Q_OBJECT
public:
    GraphicsTextAndPixmapItem(bool isLayout = false, QGraphicsItem *parent = nullptr);
    ~GraphicsTextAndPixmapItem();
    MySlot *GetInAnchor() { return mTItem->GetAnchor(); }
    MySlot *GetOutAnchor() { return mItem->GetSlot(); }
    virtual QRectF boundingRect()const override;
//    virtual void setGeometry(const QRectF &rect)override;
//    void UpdateLayout() { Invalidate(), adjustSize(); }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value)override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    /// 这个layout不能手动delete，因为在setLayout后，这个layout的控制权就交给了QGraphicsWidget，QGRaphicsWidget会在析构时
    /// delete 这个layout，如果你delete了，那么就会二次delete，导致崩溃
    QGraphicsLinearLayout *mLayout;
    std::shared_ptr<GraphicsPixmapTitleItem> mTItem;
    std::shared_ptr<GraphicsPixmapItem> mItem;
    std::shared_ptr<InfosItem> mInfos;
signals:
};

#endif // GRAPHICSTEXTANDPIXMAPITEM_H
