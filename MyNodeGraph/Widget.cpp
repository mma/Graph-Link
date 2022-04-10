#include "Widget.h"
#include "ui_Widget.h"
#include "GraphicsTextAndPixmapItem.h"
#include <QDebug>
#include <QPropertyAnimation>
#include "FlagNameItem.h"
#include "ComposeWidget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->graphicsView, &MyView::ZoomScale, this, [this](QString s){
        ui->label->setText(s);
    });
    TestFunc();
}

Widget::~Widget()
{
    // 第一种方法，当程序关闭时，就不允许调用Update方法了，以免使用已经被delet的变量
    qobject_cast<MyScene*>(ui->graphicsView->scene())->SetCanUpdate(false);
    delete ui;
}

void Widget::TestFunc()
{
    mCompose = std::make_shared<ComposeWidget>();
    ui->graphicsView->scene()->addItem(mCompose.get());

    GraphicsTextAndPixmapItem *item = new GraphicsTextAndPixmapItem();
    ui->graphicsView->scene()->addItem(item);
    item->setPos(300, 500);
    for (GraphicsTextAndPixmapItem *i : mCompose->mItems) {
        qobject_cast<MyScene *>(ui->graphicsView->scene())->AddLink(i->GetOutAnchor(), item->GetInAnchor());
    }
}

void Widget::showEvent(QShowEvent* e)
{
    static_cast<MyScene*>(ui->graphicsView->scene())->Update();
}

