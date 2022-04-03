#include "GraphicsTextAndPixmapItem.h"
#include "MyScene.h"
#include <QDebug>

GraphicsTextAndPixmapItem::GraphicsTextAndPixmapItem(bool is, QGraphicsItem *parent) : GraphicsProxyWidget(parent)
{
    if (is) {
        setFlag(ItemIsMovable, false);
    }
    mLayout = new QGraphicsLinearLayout(Qt::Orientation::Vertical);
    mTItem = std::make_shared<GraphicsPixmapTitleItem>();
    mItem = std::make_shared<GraphicsPixmapItem>();
    mLayout->addItem(mTItem.get());
    mLayout->addItem(mItem.get());
    setCenterLayout(mLayout);
}

GraphicsTextAndPixmapItem::~GraphicsTextAndPixmapItem()
{
    setLayout(nullptr);
}

QVariant GraphicsTextAndPixmapItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (scene() != nullptr) {
        static_cast<MyScene *>(scene())->Update();
    }
    return GraphicsProxyWidget::itemChange(change, value);
}
