#include "MyMenu.h"
#include <QPainter>

MyMenu::MyMenu(QWidget *parent) : QMenu(parent)
{
    mSubMenu = std::make_shared<QMenu>("new");
    QAction *ac = new QAction("close");
    QAction *ac1 = new QAction("open");
    QAction *ac2 = new QAction("save");
    QAction *ac3 = new QAction("save as another view");
    addMenu(mSubMenu.get());
    mActions.push_back(ac);
    mActions.push_back(ac1);
    mActions.push_back(ac2);
    mActions.push_back(ac3);
    addAction(ac);
    addAction(ac1);
    addAction(ac2);
    addAction(ac3);
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    QWidgetAction *wa = new QWidgetAction(mSubMenu.get());
    MenuWidget *mw = new MenuWidget();
    mMenuWidgets.push_back(mw);
    wa->setDefaultWidget(mw);
    mSubMenu->addAction(wa);
//    QMenu *ss = new QMenu("wuwuwu");
//    QAction *w = new QAction("wuwuw");
//    ss->addAction(w);
//    wa->setMenu(ss);
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
