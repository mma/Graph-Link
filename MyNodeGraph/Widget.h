#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
class ComposeWidget;
class QGraphicsLayoutItem;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void TestFunc();
    void showEvent(QShowEvent* e) override;

private:
    Ui::Widget *ui;
    std::shared_ptr<ComposeWidget> mCompose;
};
#endif // WIDGET_H
