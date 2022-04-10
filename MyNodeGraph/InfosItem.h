#ifndef INFOSITEM_H
#define INFOSITEM_H
#include "BaseGraphicsWidget.h"
#include <QGraphicsLinearLayout>
#include "GraphicsPixmapTitleItem.h"

class InfosItem : public BaseGraphicsWidget
{
    Q_OBJECT
public:
    InfosItem(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());
    ~InfosItem();

private:
    QGraphicsLinearLayout *mLayout;
    QVector<GraphicsPixmapTitleItem *> mItems;
};

#endif // INFOSITEM_H
