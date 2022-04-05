#include "Widget.h"
#include "ui_Widget.h"
#include "BaseItem.h"
#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
#include <MyGroupBox.h>
#include "GraphicsPixmapItem.h"
#include "GraphicsProxyWidget.h"
#include "GraphicsTextAndPixmapItem.h"
#include "Test.h"
#include <QDebug>
#include<QTimer>
#include <BaseGraphicsWidget.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    // For Test

    GraphicsTextAndPixmapItem *item = new GraphicsTextAndPixmapItem();

    ui->graphicsView->scene()->addItem(item);
//    item->setVisible(false);
    QGraphicsLinearLayout *linear = new QGraphicsLinearLayout();
    QGraphicsLinearLayout *linear1 = new QGraphicsLinearLayout(Qt::Orientation::Vertical);
    QGraphicsLinearLayout *linear2 = new QGraphicsLinearLayout();
    QGraphicsLinearLayout *linear3 = new QGraphicsLinearLayout();
    linear->setSpacing(0);
    linear1->setSpacing(0);
    linear2->setSpacing(0);
    linear3->setSpacing(0);
    BaseGraphicsWidget *proxy = new BaseGraphicsWidget();
    GraphicsTextAndPixmapItem *item2 = new GraphicsTextAndPixmapItem(true);
    GraphicsTextAndPixmapItem *item1 = new GraphicsTextAndPixmapItem(true);
    GraphicsTextAndPixmapItem *item3 = new GraphicsTextAndPixmapItem(true);
    GraphicsTextAndPixmapItem *item4 = new GraphicsTextAndPixmapItem(true);
    GraphicsTextAndPixmapItem *item5 = new GraphicsTextAndPixmapItem(true);
    linear3->addItem(item5);
    linear2->addStretch();
    linear2->addItem(item4);
    linear2->addStretch();

    linear->addItem(item1);
    linear->addItem(item3);
    linear->addItem(item2);
    linear1->addItem(linear3);
    linear1->addItem(linear2);
    linear1->addItem(linear);
    ui->graphicsView->scene()->addItem(proxy);
    proxy->setPos(300, 300);
    qobject_cast<MyScene *>(ui->graphicsView->scene())->AddLink(item->GetOutAnchor(), item4->GetInAnchor());

    connect(item, &GraphicsTextAndPixmapItem::Clicked, this, [=](){
        item1->setVisible(!item1->isVisible());
        item3->setVisible(!item3->isVisible());
        item2->setVisible(!item2->isVisible());
        item4->setVisible(!item4->isVisible());
        ui->graphicsView->scene()->update();;
        QTimer *t = new QTimer();
        t->setInterval(20);
        t->setSingleShot(true);
        t->start();
        connect(t, &QTimer::timeout, this, [=](){
            proxy->layout()->updateGeometry();
            proxy->adjustSize();
            delete t;
        });
    },Qt::DirectConnection);

//    item1->setVisible(false);
//    item3->setVisible(false);
//    item2->setVisible(false);
    proxy->setLayout(linear1);
//    Test();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::Test()
{
    GraphicsTextAndPixmapItem *item = new GraphicsTextAndPixmapItem();

    ui->graphicsView->scene()->addItem(item);
    GraphicsTextAndPixmapItem *item2 = new GraphicsTextAndPixmapItem(true);
    GraphicsTextAndPixmapItem *item1 = new GraphicsTextAndPixmapItem(true);
    GraphicsTextAndPixmapItem *item3 = new GraphicsTextAndPixmapItem(true);
    GraphicsTextAndPixmapItem *item4 = new GraphicsTextAndPixmapItem(true);
    GraphicsTextAndPixmapItem *item5 = new GraphicsTextAndPixmapItem(true);
    QGraphicsLinearLayout *l1 = new QGraphicsLinearLayout();
    QGraphicsLinearLayout *l3 = new QGraphicsLinearLayout();
    QGraphicsLinearLayout *l = new QGraphicsLinearLayout();
    QGraphicsLinearLayout *l2 = new QGraphicsLinearLayout(Qt::Orientation::Vertical);
    BaseGraphicsWidget *w = new BaseGraphicsWidget;

    w->setLayout(l2);
    l3->addItem(item5);
    l->addItem(item1);
    l1->addItem(item2);
    l1->addItem(item3);
    l1->addItem(item4);
    l2->addItem(l);
    l2->addItem(l3);
    l2->addItem(l1);
     ui->graphicsView->scene()->addItem(w);
     w->setPos(500, 500);
     connect(item, &GraphicsTextAndPixmapItem::Clicked, this, [=](){
         item4->setVisible(!item4->isVisible());
         item3->setVisible(!item3->isVisible());
         item2->setVisible(!item2->isVisible());
         item5->setVisible(!item5->isVisible());
         w->layout()->updateGeometry();
         w->adjustSize();
         ui->graphicsView->scene()->update();
     });
     connect(item, &GraphicsTextAndPixmapItem::Clicked1, this, [=](){
         item4->setVisible(item4->isVisible());
         item3->setVisible(item3->isVisible());
         item2->setVisible(item2->isVisible());
         item5->setVisible(item5->isVisible());
         w->layout()->updateGeometry();
         w->adjustSize();
         ui->graphicsView->scene()->update();
     });
}

