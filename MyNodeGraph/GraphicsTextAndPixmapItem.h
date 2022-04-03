#ifndef GRAPHICSTEXTANDPIXMAPITEM_H
#define GRAPHICSTEXTANDPIXMAPITEM_H
#include "GraphicsProxyWidget.h"
#include <QGraphicsLinearLayout>
#include "GraphicsPixmapItem.h"
#include "GraphicsPixmapTitleItem.h"

/// 采用QGraphicsLayout布局，但是只能是QGraphicsLayoutItem的子类
/// 所以先用BaseLayoutItem包装一下QGraphicsPixmapItem和QGraphicsSimpleTextItem
/// 然后再在QGraphicsWidget里面组装一下

class GraphicsTextAndPixmapItem : public GraphicsProxyWidget
{
    Q_OBJECT
public:
    GraphicsTextAndPixmapItem(bool isLayout = false, QGraphicsItem *parent = nullptr);
    ~GraphicsTextAndPixmapItem();
    MySlot *GetInAnchor() { return mTItem->GetAnchor(); }
    MySlot *GetOutAnchor() { return mItem->GetSlot(); }
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value)override;

private:
    /// 这个layout不能手动delete，因为在setLayout后，这个layout的控制权就交给了QGraphicsWidget，QGRaphicsWidget会在析构时
    /// delete 这个layout，如果你delete了，那么就会二次delete，导致崩溃
    QGraphicsLinearLayout *mLayout;
    std::shared_ptr<GraphicsPixmapTitleItem> mTItem;
    std::shared_ptr<GraphicsPixmapItem> mItem;
};

#endif // GRAPHICSTEXTANDPIXMAPITEM_H
