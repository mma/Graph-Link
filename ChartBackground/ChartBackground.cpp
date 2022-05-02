#include "ChartBackground.h"
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include "SelectedAtom.h"

namespace  {
constexpr int PADDING = 10;
constexpr int ICON_SIZE = 20;
}

ChartBackground::ChartBackground()
{
    InitData();
    setMouseTracking(true);
    mTitleColor = QColor(50,50,50, 155);
    mChartBackground = QColor(50,50,50, 100);
}

ChartBackground::~ChartBackground()
{
    delete mRoot;
}

void ChartBackground::InitData()
{
    mRoot = new ChartData();
    // 1W条数据就很卡了 用ScrollArea，因为所有的数据都渲染了吧
    // 方法  判断窗口显示范围，超出范围不画  20W也不卡
//    for (int i = 0; i < 2000; ++i) {
//        ChartData *t = new ChartData();
//        t->SetTitle("Title" + QString::number(i));
//        t->SetIsTitle(true);
//        t->SetHeight(20);
//        mRoot->AddChild(t);
//        mCharts.push_back(t);
//        for (int j = 0; j < 100; ++j) {
//            ChartData *data = new ChartData();
//            data->SetTitle("data" + QString::number(j));
//            data->SetHeight(60);
//            data->SetIsTitle(false);
//            mCharts.push_back(data);
//            t->AddChild(data);
//        }
//    }
    ChartData *t1 = new ChartData();
    t1->SetTitle("Title1");
    t1->SetHeight(35);
    t1->SetIsTitle(true);
    ChartData *t2 = new ChartData();
    t2->SetTitle("Title2");
    t2->SetHeight(35);
    t2->SetIsTitle(true);
    ChartData *t3 = new ChartData();
    t3->SetTitle("Title3");
    t3->SetHeight(35);
    t3->SetIsTitle(true);
    ChartData *t4 = new ChartData();
    t4->SetTitle("Title4");
    t4->SetHeight(35);
    t4->SetIsTitle(true);

    mRoot->AddChild(t1);
    mRoot->AddChild(t2);
    mRoot->AddChild(t3);
    t3->AddChild(t4);
    mCharts.push_back(t1);
    mCharts.push_back(t2);
    mCharts.push_back(t3);
    mCharts.push_back(t4);

    for (int i = 0; i < 3; i++) {
        ChartData *cd = new ChartData();
        t1->AddChild(cd);
        cd->SetTitle("data" + QString::number(i));
        cd->SetHeight(60);
        cd->SetIsTitle(false);
        mCharts.push_back(cd);
    }
    for (int i = 0; i < 3; i++) {
        ChartData *cd = new ChartData();
        t2->AddChild(cd);
        cd->SetTitle("data" + QString::number(i));
        cd->SetHeight(60);
        cd->SetIsTitle(false);
        mCharts.push_back(cd);
    }
    for (int i = 0; i < 3; i++) {
        ChartData *cd = new ChartData();
        t4->AddChild(cd);
        cd->SetTitle("data" + QString::number(i));
        cd->SetHeight(60);
        cd->SetIsTitle(false);
        mCharts.push_back(cd);
    }
    CalculateSize();
}

void ChartBackground::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
    QPainter p(this);
    p.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
    int y = 0;
    PaintNode(p, mRoot, y);
}

// 针对scrollarea的，把chartdata的全部坐标转为当前视口的坐标
int maptowindow(int t, std::function<int()> f)
{
    return t - f();
}

void ChartBackground::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    for (ChartData *cd : mCharts) {
        if (cd->mIsDraging) {
//            int local = maptowindow(cd->mY, cFunc);
//            int distance = cd->mPressedY - local;
            cd->mDragingY = event->y() - cd->mPressedYDistance + cFunc();
            // 判断
            SwapChart(cd);
            break;
        }
    }
    update();
}

void ChartBackground::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    for (ChartData *cd : mCharts) {
        QRect rc(0, cd->mY, width(), cd->GetHeight());
        if (rc.contains(event->pos()) && cd->mIsTitle && cd->mShow && event->button() == Qt::LeftButton) {
            QRect selectedRect(width() - rc.height(), rc.y(), rc.height(), rc.height());
            if (selectedRect.contains(event->pos())) {
                SelectedAtom atom;
                if (atom.exec()) {
                    qDebug() << atom.GetSelected().size();
                } else {
                    qDebug() << "取消了";
                }
                break;
            }
            cd->SetChildrenHideOrShow();
            CalculateSize();
            break;
        } else if (rc.contains(event->pos()) /*&& !cd->mIsTitle*/ && cd->mShow && event->button() == Qt::RightButton) {
            cd->mIsDraging = true;
            int pressedY = event->y();
            int local = maptowindow(cd->mY, cFunc);
            cd->mPressedYDistance = pressedY - local;
            cd->mDragingY = event->y() - cd->mPressedYDistance + cFunc();
            break;
        }
    }
    update();
}

void ChartBackground::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    for (ChartData *cd : mCharts) {
        cd->mIsDraging = false;
    }
    update();
}

void ChartBackground::PaintNode(QPainter &p, ChartData *data, int &y)
{
    ChartData *dragData = nullptr;
    for (ChartData *cd : mCharts) {
        if (!ParentIsShow(cd)) {
            continue;
        }
        if (!cd->mShow) {
            continue;
        }
        if (cd->mY + cd->GetHeight() < cFunc()) {
            continue;
        }
        if (cd->mY > cFunc() + pFunc()) {
            break;
        }
        QRect rc;
        if (cd->mIsDraging) {
            dragData = cd;
        } else {
            rc = QRect(0, cd->mY, width(), cd->GetHeight());
        }
        if (cd->mIsTitle) {
            p.fillRect(rc.adjusted(0, 1, 0, -1), mTitleColor);
            // 测试
            QRect selectedRect(width() - rc.height(), rc.y(), rc.height(), rc.height());
            p.drawRect(selectedRect.adjusted(5, 5, -5, -5));
            QPainterPath path;
            QRect tmp = selectedRect.adjusted(5, 5, -5, -5);
            path.moveTo(QPoint(tmp.x(), tmp.center().y())/*, QPoint(tmp.center().x(), tmp.y() + tmp.height())*/);
            path.lineTo(QPoint(tmp.center().x(), tmp.y() + tmp.height()));
            path.lineTo(selectedRect.x() + selectedRect.width(), selectedRect.y());
            p.save();
            QPen pen = p.pen();
            pen.setWidthF(1.5);
            p.setPen(pen);
            p.drawPath(path);
            p.restore();
        } else {
            p.fillRect(rc.adjusted(0, 1, 0, -1), mChartBackground);
        }
        QString info = cd->GetTitle();
        int level = cd->GetLevel() - 1;
        if (cd->mIsTitle) {
            int size = 0;
            if (rc.height() > ICON_SIZE) {
                size = ICON_SIZE;
            } else {
                size = rc.height();
            }
            if (cd->mChildrenShow) {
                QRect icon(20 * level + PADDING, rc.y(), ICON_SIZE, rc.height());
                p.drawLine(QPoint(icon.center().x() - size / 2, icon.center().y()), QPoint(icon.center().x() + size / 2, icon.center().y()));
                rc.adjust(PADDING + ICON_SIZE, 0, 0, 0);
            } else {
                QRect icon(20 * level + PADDING, rc.y(), ICON_SIZE, rc.height());
                p.drawLine(QPoint(icon.center().x(), icon.center().y() - size / 2), QPoint(icon.center().x(), icon.center().y() + size / 2));
                p.drawLine(QPoint(icon.center().x() - size / 2, icon.center().y()), QPoint(icon.center().x() + size / 2, icon.center().y()));
                rc.adjust(PADDING + ICON_SIZE, 0, 0, 0);
            }
            p.drawText(rc.adjusted(20 * level + PADDING, 0, 0, 0), Qt::AlignVCenter, info);
        } else {
            p.drawText(rc.adjusted(PADDING, 0, 0, 0), Qt::AlignVCenter, info);
        }
    }
    if (dragData == nullptr) {
        return;
    }
    QRect rc(0, dragData->mDragingY, width(), dragData->GetHeight());
    p.fillRect(rc.adjusted(0, 1, 0, -1), mChartBackground);
     p.drawText(rc.adjusted(PADDING, 0, 0, 0), Qt::AlignVCenter, dragData->GetTitle());

//    for (ChartData *cd : data->GetChildren()) {
//        if (!cd->mShow) {
//            continue;
//        }
//        QRect rc(0, y, width(), cd->GetHeight());
//        cd->mY = y;
//        y += cd->GetHeight();
//        if (cd->mIsTitle) {
//            p.fillRect(rc.adjusted(0, 1, 0, -1), Qt::gray);
//        } else {
//            p.fillRect(rc.adjusted(0, 1, 0, -1), Qt::lightGray);
//        }
//        QString info = cd->GetTitle();
//        int level = cd->GetLevel() - 1;
//        if (cd->mIsTitle) {
//            p.drawText(rc.adjusted(20 * level, 0, 0, 0), Qt::AlignVCenter, info);
//        } else {
//            p.drawText(rc, Qt::AlignVCenter, info);
//        }
//        PaintNode(p, cd, y);
    //    }
}

bool ChartBackground::ParentIsShow(ChartData *cd)
{
    ChartData *parent = cd->mParent;
    while (parent) {
        if (!parent->mChildrenShow) {
            return false;
        }
        parent = parent->mParent;
    }
    return true;
}

// 只需要在改变了显示个数，上下关系的时候更新一下
void ChartBackground::CalculateSize()
{
    // 这边计算每个title的children高度,方便计算拖拽判断范围
//    mAllTitles.clear();
//    FindAllTitles(mRoot);
//    std::sort(mAllTitles.begin(), mAllTitles.end(), [](ChartData *a, ChartData *b)->bool{
//        if (a->GetLevel() > b->GetLevel()) {
//            return true;
//        }
//        return false;
//    });
//    for (ChartData *cd : mAllTitles) {
//        if (!cd->mChildrenShow) {
//            continue;
//        }
//        if (cd->GetChildren().size() > 0 && !cd->GetChildren()[0]->mIsTitle) {
//            for (int i = 0; i < cd->GetChildren().size(); ++i) {
//                cd->mAllChildrenHeight += cd->GetChildren()[i]->GetHeight();
//            }
//        } else {
//            for (ChartData *data : cd->GetChildren()) {
//                cd->mAllChildrenHeight += data->mAllChildrenHeight;
//            }
//        }
//    }
//    mRoot->mAllChildrenHeight = 0;
//    for (ChartData *cd : mRoot->GetChildren()) {
//        mRoot->mAllChildrenHeight += cd->mAllChildrenHeight;
//    }
//    setFixedHeight(mRoot->mAllChildrenHeight);

    int y = 0;

    clock_t startTime, endTime;
    startTime = clock();//计时开始
    CalculatePosition(mRoot, y);
    endTime = clock();//计时结束
    qDebug() << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s";
    setFixedHeight(y);
    // 根据y的位置排序，方便paint
    std::sort(mCharts.begin(), mCharts.end(), [](ChartData *a, ChartData *b){
        if (a->mY < b->mY) {
            return true;
        }
        return false;
    });
}

void ChartBackground::CalculatePosition(ChartData *data, int &y)
{
    for (ChartData *cd : data->GetChildren()) {
        if (!cd->mShow) {
            cd->mY = y;
            continue;
        }
        else {
            cd->mY = y;
            y += cd->GetHeight();
        }
        CalculatePosition(cd, y);
    }
}

void ChartBackground::FindAllTitles(ChartData *data)
{
    if (data->GetChildren().size() > 0) {
        for (ChartData *cd : data->GetChildren()) {
            cd->mAllChildrenHeight = cd->GetHeight();
            if (cd->mIsTitle) {
                mAllTitles.push_back(cd);
            }
            FindAllTitles(cd);
        }
    }
}

void ChartBackground::SwapChart(ChartData *data)
{
    ChartData *parent = data->mParent;
    int index = parent->GetChildren().indexOf(data);
    ChartData *prev = nullptr;
    ChartData *next = nullptr;
    if (parent->GetChildren().size() <= 1) {
        return;
    }
    if (index == 0) {
        next = parent->GetChildren()[index + 1];
    } else if (index == parent->GetChildren().size() - 1) {
        prev = parent->GetChildren()[index - 1];
    } else {
        next = parent->GetChildren()[index + 1];
        prev = parent->GetChildren()[index - 1];
    }
    if (prev != nullptr) {
        if (data->mDragingY < (prev->mY + prev->mY + prev->GetHeight()) / 2) {
            parent->GetChildren().swapItemsAt(index, index - 1);
            // TODO : 尝试做动画效果, 不调用Calculate，交换Y
            CalculateSize();
            return;
        }
    }
    if (next != nullptr) {
        if (data->mDragingY + data->GetHeight() > (next->mY + next->GetHeight() + next->mY) / 2) {
            parent->GetChildren().swapItemsAt(index, index + 1);
            // TODO : 尝试做动画效果
            CalculateSize();
            return;
        }
    }
}
