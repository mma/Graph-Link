#ifndef CHARTDATA_H
#define CHARTDATA_H
#include <QObject>
#include <functional>

struct DataPoint {
    qreal mTime;
    qreal mValue;
};

class ChartData
{
public:
    ChartData();
    ~ChartData();
    void AddChild(ChartData *cd);
    void SetHeight(int h);
    int GetHeight();
    void SetChildrenHideOrShow();
    void SetTitle(QString str);
    QString GetTitle();
    void SetIsTitle(bool f);
    int GetLevel();
    QVector<ChartData *> &GetChildren();
    bool mShow = true;
    bool mChildrenShow = true;
    bool mIsTitle = false;
    ChartData *mParent = nullptr;
    int mY = 0;
    int mAllChildrenHeight = 0;
    bool mIsDraging = false;
    int mDragingY = 0;
    int mPressedYDistance = 0;

private:
    int mHeight = 0;
    QVector<ChartData *> mChildren;
    QVector<DataPoint> mPoints;
    int mLevel = 0;
    QString mTitle = "Undefined";
};

#endif // CHARTDATA_H
