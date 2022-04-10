#include "FlagNameItem.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>

namespace  {
constexpr qreal MARGIN = 12.0;
constexpr qreal INNER_SPACING = 5.0;
constexpr qreal INNER_MARGIN = 5.0;
constexpr qreal BORDER_RADIUS = 5.0;
}
FlagNameItem::FlagNameItem(QGraphicsLayoutItem *parent, bool isLayout) : BaseLayoutItem(parent, isLayout)
{
    mItemSize = QSize(250, 80);
    setAcceptHoverEvents(true);
    mLabel = "this is just a simple demo !!!";
}

FlagNameItem::~FlagNameItem()
{

}

void FlagNameItem::hoverEnterEvent(QGraphicsSceneHoverEvent *e)
{
    QGraphicsObject::hoverMoveEvent(e);
    update();
}

void FlagNameItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *e)
{
    QGraphicsObject::hoverLeaveEvent(e);
    update();
}

void FlagNameItem::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    QGraphicsObject::mousePressEvent(e);
    Clicked();
}

void FlagNameItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    QPen pen = painter->pen();
    QRectF rect = boundingRect();
    QRectF borderRect = rect.adjusted(MARGIN, MARGIN, -MARGIN, -MARGIN);
    painter->setPen(Qt::NoPen);
    if (option->state.testFlag(QStyle::State_MouseOver)) {
        painter->setBrush(QColor(58,139,243));
        painter->drawRoundedRect(rect, 8, 8);
    }
    painter->setBrush(QColor(222,196,136));
    painter->drawRoundedRect(borderRect, BORDER_RADIUS, BORDER_RADIUS);
    QRectF contentsRect = borderRect.adjusted(INNER_MARGIN, INNER_MARGIN, -INNER_MARGIN, -INNER_MARGIN);
    QRectF flag(contentsRect.x(), contentsRect.y(), contentsRect.height(), contentsRect.height());
    painter->fillRect(flag, QColor(225,173,111));
    painter->setPen(pen);
    painter->save();
    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(flag.height() / 2);
    painter->setFont(font);
    painter->drawText(flag, Qt::AlignCenter, "R");
    painter->restore();
    QRectF labelRect = contentsRect.adjusted(flag.width() + INNER_SPACING, 0, 0, 0);
    QString label = painter->fontMetrics().elidedText(mLabel, Qt::ElideMiddle, labelRect.width());
    painter->drawText(labelRect, Qt::AlignCenter, label);
}

QPainterPath FlagNameItem::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void FlagNameItem::setGeometry(const QRectF &rect)
{
    prepareGeometryChange();
    QGraphicsLayoutItem::setGeometry(rect);
    setPos(rect.topLeft());
}
