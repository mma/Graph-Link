#include "MyView.h"
#include <QWheelEvent>
#include <qmath.h>

MyView::MyView(QWidget *parent) : QGraphicsView(parent)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    mScene = std::make_shared<MyScene>(this);
    setScene(mScene.get());
    setDragMode(DragMode::RubberBandDrag);
}

MyView::~MyView()
{

}

void MyView::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() == Qt::ControlModifier) {
        qreal scaleFactor = qPow(2.0, event->angleDelta() / 240.0); //How fast we zoom
        qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
        if(0.05 < factor && factor < 10) {//Zoom factor limitation
            scale(scaleFactor, scaleFactor);
            ZoomScale(QString::number(factor * 100) + "%");
        }
    }
}

void MyView::showEvent(QShowEvent *event)
{
    qobject_cast<MyScene *>(scene())->Update();
}
