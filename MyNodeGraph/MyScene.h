#ifndef MYSCENE_H
#define MYSCENE_H
#include <QGraphicsScene>
#include "MySlot.h"
#include "NodeLink.h"

class MyScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MyScene(QObject *parent = nullptr);
    void AddLink(MySlot *s1, MySlot *s2);
    QVector<NodeLink *> links;
    void Update();
    void SetCanUpdate(bool f) { mCanUpdate = f; }

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    bool mCanUpdate = true;
};

#endif // MYSCENE_H
