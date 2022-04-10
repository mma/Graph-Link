#include "MyMenu.h"
#include <QPainter>
#include <QGraphicsDropShadowEffect>

MyMenu::MyMenu(QWidget *parent) : QMenu(parent)
{
    mSubMenu = std::make_shared<QMenu>("new");
    QAction *ac = new QAction("close");
    QAction *ac1 = new QAction("open");
    QAction *ac2 = new QAction("save");
    QAction *ac3 = new QAction("save as another view");
    addMenu(mSubMenu.get());
    addSeparator();
    mActions.push_back(ac);
    mActions.push_back(ac1);
    mActions.push_back(ac2);
    mActions.push_back(ac3);
    addAction(ac);
    addAction(ac1);
    addAction(ac2);
    addAction(ac3);
    // pop menu的基本属性，不加这个menu点其他位置不消失
    // framelesswindowhint 如果设置圆角需要这个，让他变成无边框， 显示圆角
    // nodropshawWindowhint 不显示阴影，因为默认右侧与下侧有阴影，所以导致右下角不显示圆角
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    // 设置背景透明，让四个角只显示圆角，不显示其他黑的部分
    setAttribute(Qt::WA_TranslucentBackground);
    mSubMenu->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    mSubMenu->setAttribute(Qt::WA_TranslucentBackground);
    for (int i = 0; i < 5; ++i) {
        QWidgetAction *wa = new QWidgetAction(mSubMenu.get());
        MenuWidget *mw = new MenuWidget();
        mMenuWidgets.push_back(mw);
        wa->setDefaultWidget(mw);
        mSubMenu->addAction(wa);
    }
    // 如果需要自己加阴影， 用QGraphicsDropShadowEffect， 需要用qss 设置QMenu的margin 比0大， 否则没位置显示阴影

//    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
//    shadow->setOffset(0, 0);
//    shadow->setColor(QColor("#444444"));
//    shadow->setBlurRadius(10);
//    setGraphicsEffect(shadow);
}

MyMenu::MyMenu(const QString &title, QWidget *parent) : MyMenu(parent)
{
    setTitle(title);
}

MyMenu::~MyMenu()
{
    for (MenuWidget *ac : mMenuWidgets) {
        delete ac;
    }
    for (QAction *ac : mActions) {
        delete ac;
    }
}

MenuWidget::MenuWidget(QWidget *parent) : QWidget(parent)
{
    mLayout = std::make_shared<QHBoxLayout>();
    setLayout(mLayout.get());
    mLayout->setSpacing(30);
    mImg = std::make_shared<QLabel>("???");
    QPixmap pix(20, 20);
    pix.fill(Qt::gray);
    mImg->setPixmap(pix);
    mInfo = std::make_shared<QLabel>("info");
    mLayout->addWidget(mImg.get());
    mLayout->addWidget(mInfo.get());
    setMouseTracking(true);
}

MenuWidget::~MenuWidget()
{

}

void MenuWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    if (mIsActived) {
        p.setBrush(QColor(173, 216, 230));
        p.drawRoundedRect(rect(), 5, 5);
    }
    QWidget::paintEvent(event);
}
#include <QDebug>
void MenuWidget::enterEvent(QEvent *event)
{
    qDebug() << "enter";
    mIsActived = true;
    update();
    QWidget::enterEvent(event);
}

void MenuWidget::leaveEvent(QEvent *event)
{
    qDebug() << "leave";
    mIsActived = false;
    update();
    QWidget::leaveEvent(event);
}
