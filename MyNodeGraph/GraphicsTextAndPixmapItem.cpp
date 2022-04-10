#include "GraphicsTextAndPixmapItem.h"
#include "MyScene.h"
#include <QDebug>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QStyleOptionGraphicsItem>

GraphicsTextAndPixmapItem::GraphicsTextAndPixmapItem(bool is, QGraphicsItem *parent) : BaseGraphicsWidget(parent)
{
//    if (is) {
        setFlag(ItemIsMovable, false);
        setFlag(ItemIsSelectable, false);
//    }
    mLayout = new QGraphicsLinearLayout(Qt::Orientation::Vertical);
    mTItem = std::make_shared<GraphicsPixmapTitleItem>();
    mItem = std::make_shared<GraphicsPixmapItem>();
    mInfos = std::make_shared<InfosItem>();
    mLayout->setSpacing(0);
    mLayout->addItem(mTItem.get());
    mLayout->addItem(mItem.get());
    mLayout->addItem(mInfos.get());
    setLayout(mLayout);
    adjustSize();
}

GraphicsTextAndPixmapItem::~GraphicsTextAndPixmapItem()
{
    setLayout(nullptr);
    qDebug() << "delete le ";
}

QRectF GraphicsTextAndPixmapItem::boundingRect() const
{
    return QRectF(0, 0, this->sizeHint(Qt::PreferredSize).width(), this->sizeHint(Qt::PreferredSize).height());
}

void GraphicsTextAndPixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(58,139,243));
    if (option->state.testFlag(QStyle::State_MouseOver)) {
        painter->drawRoundedRect(boundingRect(), 10, 10);
    }
}

QVariant GraphicsTextAndPixmapItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (scene() != nullptr) {
        static_cast<MyScene *>(scene())->Update();
    }
    return BaseGraphicsWidget::itemChange(change, value);
}

void GraphicsTextAndPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
}
