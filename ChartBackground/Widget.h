#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "ChartBackground.h"
#include "ChartData.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    int GetCurrent();
    int GetPageStep();
protected:

private:
    Ui::Widget *ui;
    std::shared_ptr<ChartBackground> mWidget;
};
#endif // WIDGET_H
