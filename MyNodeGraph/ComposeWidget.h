#ifndef COMPOSEWIDGET_H
#define COMPOSEWIDGET_H
#include "BaseGraphicsWidget.h"
#include <QGraphicsLinearLayout>
#include <QPropertyAnimation>
#include "GraphicsTextAndPixmapItem.h"
#include "FlagNameItem.h"
#include <QAction>
#include <QMenu>

class ComposeWidget : public BaseGraphicsWidget
{
    Q_OBJECT
    Q_PROPERTY(QSizeF rs READ getRS WRITE setRS)
public:
    ComposeWidget(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());
    ~ComposeWidget();
    QSizeF getRS() { return rs; };
    void setRS(QSizeF f);
    QVector<GraphicsTextAndPixmapItem *> mItems;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant& value)override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

private:
    QGraphicsLinearLayout *mVLayout;
    QGraphicsLinearLayout *mHFlagLayout;
    QGraphicsLinearLayout *mHContentsLayout;

    std::shared_ptr<FlagNameItem> mFlag;

    std::shared_ptr<GraphicsTextAndPixmapItem> mtap1;
    std::shared_ptr<GraphicsTextAndPixmapItem> mtap2;
    std::shared_ptr<GraphicsTextAndPixmapItem> mtap3;

    std::shared_ptr<QPropertyAnimation> mAnimation;

    std::shared_ptr<QMenu> mMenu;
    std::shared_ptr<QMenu> mSubMenu;
    QVector<QAction *> mActions;
    bool mZoomIn = false;
    QSizeF rs;

private slots:
    void StateChange();
    void SizeChanged(const QVariant &value);

};

#endif // COMPOSEWIDGET_H
