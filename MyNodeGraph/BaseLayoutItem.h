#ifndef BASELAYOUTITEM_H
#define BASELAYOUTITEM_H
#include <QGraphicsLayoutItem>

class BaseLayoutItem : public QGraphicsLayoutItem
{
public:
    BaseLayoutItem(QGraphicsLayoutItem *parent = nullptr, bool isLayout = false);
    ~BaseLayoutItem();

protected:
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const override;
};

#endif // BASELAYOUTITEM_H
