#include "ComposeWidget.h"
#include <QDebug>
#include <QPainter>

ComposeWidget::ComposeWidget(QGraphicsItem *parent, Qt::WindowFlags wFlags) : BaseGraphicsWidget(parent, wFlags)
{
    mVLayout = new QGraphicsLinearLayout(Qt::Orientation::Vertical);
    mHFlagLayout = new QGraphicsLinearLayout(Qt::Orientation::Horizontal);
    mHContentsLayout = new QGraphicsLinearLayout(Qt::Orientation::Horizontal);
    mVLayout->addItem(mHFlagLayout);
    mVLayout->setSpacing(0);
    mVLayout->addItem(mHContentsLayout);

    mHContentsLayout->addStretch();
    mtap1 = std::make_shared<GraphicsTextAndPixmapItem>();
    mHContentsLayout->addItem(mtap1.get());
    mtap2 = std::make_shared<GraphicsTextAndPixmapItem>();
    mHContentsLayout->addItem(mtap2.get());
    mtap3 = std::make_shared<GraphicsTextAndPixmapItem>();
    mHContentsLayout->addItem(mtap3.get());
    mHContentsLayout->addStretch();

    mFlag = std::make_shared<FlagNameItem>();
    mHFlagLayout->addStretch();
    mHFlagLayout->addItem(mFlag.get());
    mHFlagLayout->addStretch();

    setLayout(mVLayout);

    mAnimation = std::make_shared<QPropertyAnimation>(this, "rs");
    connect(mFlag.get(), &FlagNameItem::Clicked, this, &ComposeWidget::StateChange);
    connect(mAnimation.get(), &QPropertyAnimation::valueChanged, this, &ComposeWidget::SizeChanged);

    mItems.push_back(mtap1.get());
    mItems.push_back(mtap2.get());
    mItems.push_back(mtap3.get());

    mMenu = std::make_shared<MyMenu>();
}

ComposeWidget::~ComposeWidget()
{

}
/// 对比这两个信号的方式
/// 一个是正常使用Q_PROPERTY ，一个绑定的valueChanged信号
/// 发现一个区别，valuechanged除了第一次外，下一次的开始值并不是startValue，而是上一次的结束值，然后是startValue
/// 而Q_PROPERTY的 WRITE 是正常的每次从startValue开始改变
void ComposeWidget::SizeChanged(const QVariant &value)
{
    //qDebug() << value.toSizeF() << "??";
}

void ComposeWidget::setRS(QSizeF f)
{
    rs = f;
    //qDebug() << f;
    resize(f);
    if (mZoomIn && property("mysize").toSizeF() == f) {
        mtap1->setVisible(!mtap1->isVisible());
        mtap2->setVisible(!mtap2->isVisible());
        mtap3->setVisible(!mtap3->isVisible());
    }
}

void ComposeWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    painter->setBrush(QColor(211, 211, 211));
    painter->drawRoundedRect(boundingRect(), 5, 5);
}
#include "MyScene.h"
QVariant ComposeWidget::itemChange(GraphicsItemChange change, const QVariant& value)
{
    return QGraphicsWidget::itemChange(change, value);
}
#include <QGraphicsSceneContextMenuEvent>
void ComposeWidget::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    mMenu->exec(QCursor::pos());
}

void ComposeWidget::StateChange()
{
    mtap1->setVisible(!mtap1->isVisible());
    mtap2->setVisible(!mtap2->isVisible());
    mtap3->setVisible(!mtap3->isVisible());
    Invalidate();
    mtap1->UpdateLayout();
    mtap2->UpdateLayout();
    mtap3->UpdateLayout();
    QSizeF sz = effectiveSizeHint(Qt::SizeHint::PreferredSize);
    mZoomIn = false;
    setProperty("mysize", sz);
    if (mtap1->isVisible()) {
        mZoomIn = true;
        mtap1->setVisible(!mtap1->isVisible());
        mtap2->setVisible(!mtap2->isVisible());
        mtap3->setVisible(!mtap3->isVisible());
    }
    mAnimation->setStartValue(size());
//    qDebug() << "start" << "****" << size();
    mAnimation->setEndValue(sz);
//    qDebug() << "start" << "****" << sz;
    mAnimation->setDuration(333);
    mAnimation->start();
}
