#include "Test.h"

Test::Test(QGraphicsLayoutItem *parent, bool is)
{
    mLayout = new QGraphicsLinearLayout();
    mTItem = new GraphicsPixmapTitleItem();
    mItem = new GraphicsPixmapItem();
    mLayout->addItem(mTItem);
    mLayout->addItem(mItem);
    mLayout->setParentLayoutItem(this);
}

Test::~Test()
{

}
