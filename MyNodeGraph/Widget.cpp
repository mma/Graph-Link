#include "Widget.h"
#include "ui_Widget.h"
#include "BaseItem.h"
#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
#include <MyGroupBox.h>
#include "BaseLayoutItem.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    BaseItem *b1 = new BaseItem();
    BaseItem *b2 = new BaseItem(BaseItem::LEFT);
    BaseItem *b3 = new BaseItem(BaseItem::LEFT);
    BaseItem *b4 = new BaseItem(BaseItem::DOWN);
    MyGroupBox *gb = new MyGroupBox();
    ui->graphicsView->scene()->addItem(b1);
    ui->graphicsView->scene()->addItem(gb);
    ui->graphicsView->scene()->addItem(b2);
    ui->graphicsView->scene()->addItem(b3);
    ui->graphicsView->scene()->addItem(b4);
    gb->AddItem(b1);
    gb->AddItem(b3);
    gb->AddItem(b4);
    b2->setPos(300, 300);
    qobject_cast<MyScene *>(ui->graphicsView->scene())->AddLink(b1->GetSlot(), b2->GetSlot());
    qobject_cast<MyScene *>(ui->graphicsView->scene())->AddLink(b2->GetSlot(), b4->GetSlot());
}

Widget::~Widget()
{
    delete ui;
}

