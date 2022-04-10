#ifndef MYVIEW_H
#define MYVIEW_H
#include <QGraphicsView>
#include "MyScene.h"
class MyView : public QGraphicsView
{
    Q_OBJECT
public:
    MyView(QWidget *parent = nullptr);
    ~MyView();

protected:
    virtual void wheelEvent(QWheelEvent* event);
    void showEvent(QShowEvent *event) override;

private:
    std::shared_ptr<MyScene> mScene;

signals:
    void ZoomScale(QString s);
};

#endif // MYVIEW_H
