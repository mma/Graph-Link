#include "MyScene.h"
#include <QPainter>
#include <QDebug>

MyScene::MyScene(QObject *parent) : QGraphicsScene(parent)
{

}

void MyScene::AddLink(MySlot *s1, MySlot *s2)
{
    NodeLink *l = new NodeLink(s1, s2);
    l->updateShape();
    links.push_back(l);
    addItem(l);
}

void MyScene::Update()
{
    if (mCanUpdate) {
        for (int i = 0; i < links.size(); i++) {
            links[i]->updateShape();
        }
    }
}

void MyScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    const int gridSize = 50;

    const qreal left = int(rect.left()) - (int(rect.left()) % gridSize);
    const qreal top = int(rect.top()) - (int(rect.top()) % gridSize);

    QVarLengthArray<QLineF, 100> lines;

    for (qreal x = left; x < rect.right(); x += gridSize)
        lines.append(QLineF(x, rect.top(), x, rect.bottom()));
    for (qreal y = top; y < rect.bottom(); y += gridSize)
        lines.append(QLineF(rect.left(), y, rect.right(), y));

    painter->setRenderHint(QPainter::Antialiasing, true);

    painter->setPen(QColor(Qt::lightGray).lighter(110));
    painter->drawLines(lines.data(), lines.size());
//    painter->setPen(Qt::black);
}
