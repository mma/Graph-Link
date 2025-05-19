#ifndef MYMENU_H
#define MYMENU_H
#include <QMenu>
#include <QWidgetAction>
#include <QHBoxLayout>
#include <QPixmap>
#include <QLabel>

class MenuWidget;
class MyMenu : public QMenu
{
public:
    MyMenu(QWidget *parent = nullptr);
    MyMenu(const QString &title, QWidget *parent = nullptr);
    ~MyMenu();

private:
    QVector<QAction *> mActions;
    std::shared_ptr<QMenu> mSubMenu;
    QVector<MenuWidget *> mMenuWidgets;
};

class MenuWidget : public QWidget
{
    Q_OBJECT
public:
    MenuWidget(QWidget *parent = 0);
    ~MenuWidget();

protected:
    void paintEvent(QPaintEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    std::shared_ptr<QHBoxLayout> mLayout;
    std::shared_ptr<QLabel> mImg;
    std::shared_ptr<QLabel> mInfo;
    bool mIsActived = false;
};

#endif // MYMENU_H
