#include "Widget.h"
#include "ui_Widget.h"
#include "BaseItem.h"
#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
#include <MyGroupBox.h>
#include "GraphicsPixmapItem.h"
#include "GraphicsProxyWidget.h"
#include "GraphicsTextAndPixmapItem.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    // For Test

    GraphicsTextAndPixmapItem *item = new GraphicsTextAndPixmapItem();

    ui->graphicsView->scene()->addItem(item);

    QGraphicsLinearLayout *linear = new QGraphicsLinearLayout();
    GraphicsProxyWidget *proxy = new GraphicsProxyWidget();
    GraphicsTextAndPixmapItem *item2 = new GraphicsTextAndPixmapItem(true);
    GraphicsTextAndPixmapItem *item1 = new GraphicsTextAndPixmapItem(true);
    GraphicsTextAndPixmapItem *item3 = new GraphicsTextAndPixmapItem(true);
    linear->addItem(item1);
    linear->addItem(item3);
    linear->addItem(item2);
    proxy->setCenterLayout(linear);
    ui->graphicsView->scene()->addItem(proxy);
    proxy->setPos(300, 300);
    qobject_cast<MyScene *>(ui->graphicsView->scene())->AddLink(item->GetOutAnchor(), item1->GetInAnchor());
    qobject_cast<MyScene *>(ui->graphicsView->scene())->AddLink(item->GetOutAnchor(), item2->GetInAnchor());
    qobject_cast<MyScene *>(ui->graphicsView->scene())->AddLink(item->GetOutAnchor(), item3->GetInAnchor());
}

Widget::~Widget()
{
    delete ui;
}

