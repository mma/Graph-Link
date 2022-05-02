#include "ChartData.h"

ChartData::ChartData()
{

}

ChartData::~ChartData()
{
    qDeleteAll(mChildren);
}

void ChartData::AddChild(ChartData *cd)
{
    mChildren.push_back(cd);
    cd->mParent = this;
    cd->mLevel = mLevel + 1;
}

void ChartData::SetHeight(int h)
{
    mHeight = h;
    mAllChildrenHeight = mHeight;
}

int ChartData::GetHeight()
{
    return mHeight;
}

void ChartData::SetChildrenHideOrShow()
{
    mChildrenShow = !mChildrenShow;
    for (ChartData *cd : mChildren) {
        cd->mShow = !cd->mShow;
    }
}

void ChartData::SetTitle(QString str)
{
    mTitle = str;
}

QString ChartData::GetTitle()
{
    return mTitle;
}

void ChartData::SetIsTitle(bool f)
{
    mIsTitle = f;
}

int ChartData::GetLevel()
{
    return mLevel;
}

QVector<ChartData *> &ChartData::GetChildren()
{
    return mChildren;
}
