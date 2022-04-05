#include "GraphicsTextAndPixmapItem.h"
#include "MyScene.h"
#include <QDebug>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
GraphicsTextAndPixmapItem::GraphicsTextAndPixmapItem(bool is, QGraphicsItem *parent) : BaseGraphicsWidget(parent)
{
    if (is) {
        setFlag(ItemIsMovable, false);
        setFlag(ItemIsSelectable, false);
    }
    mLayout = new QGraphicsLinearLayout(Qt::Orientation::Vertical);
    mTItem = std::make_shared<GraphicsPixmapTitleItem>();
    mItem = std::make_shared<GraphicsPixmapItem>();
    mLayout->addItem(mTItem.get());
    mLayout->addItem(mItem.get());
//    setCenterLayout(mLayout);
    mLayout->setSpacing(0);
    setLayout(mLayout);
    adjustSize();
    setContentsMargins(0, 0, 0, 0);
}

GraphicsTextAndPixmapItem::~GraphicsTextAndPixmapItem()
{
    setLayout(nullptr);
}

QRectF GraphicsTextAndPixmapItem::boundingRect() const
{
    return QRectF(0, 0, this->sizeHint(Qt::PreferredSize).width(), this->sizeHint(Qt::PreferredSize).height());
}

void GraphicsTextAndPixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen p = painter->pen();
    p.setColor(Qt::red);
    painter->setPen(p);
    painter->drawRect(rect());
    BaseGraphicsWidget::paint(painter, option, widget);
}

QVariant GraphicsTextAndPixmapItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (scene() != nullptr) {
        static_cast<MyScene *>(scene())->Update();
    }
    return BaseGraphicsWidget::itemChange(change, value);
//        return QGraphicsItem::itemChange(change, value);
}

void GraphicsTextAndPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::MouseButton::LeftButton) {
        Clicked();
    }
//    if (event->button() == Qt::MouseButton::RightButton) {
//        Clicked1();
//    }
}
