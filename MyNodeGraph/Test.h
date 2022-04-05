#ifndef TEST_H
#define TEST_H
#include "BaseLayoutItem.h"
#include "GraphicsPixmapItem.h"
#include "GraphicsPixmapTitleItem.h"
#include <QGraphicsLinearLayout>

class Test : public BaseLayoutItem
{
    Q_OBJECT
public:
    Test(QGraphicsLayoutItem *parent = nullptr, bool is = false);
    ~Test();
    MySlot *GetInSlot() { return mTItem->GetAnchor(); }
    MySlot *GetOutSlot() { return mItem->GetSlot(); }
private:
    GraphicsPixmapItem *mItem;
    GraphicsPixmapTitleItem *mTItem;
    QGraphicsLinearLayout *mLayout;
};

#endif // TEST_H
