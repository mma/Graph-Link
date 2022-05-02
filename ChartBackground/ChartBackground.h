#ifndef CHARTBACKGROUND_H
#define CHARTBACKGROUND_H

#include <QWidget>
#include "ChartData.h"

class ChartBackground : public QWidget
{
    Q_OBJECT
public:
    ChartBackground();
    ~ChartBackground();
    void InitData();
    void RegisterCurrent(std::function<int()> f){cFunc = f;}
    void RegisterPageStep(std::function<int()> f){pFunc = f;}
protected:
    void paintEvent(QPaintEvent *e) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    ChartData *mRoot = nullptr;
    QVector<ChartData *> mCharts;
    QVector<ChartData *> mAllTitles;
    QColor mTitleColor;
    QColor mChartBackground;

    void PaintNode(QPainter &p, ChartData *data, int &y);
    bool ParentIsShow(ChartData *cd);
    void CalculateSize();
    void CalculatePosition(ChartData *data, int &y);
    void FindAllTitles(ChartData *data);
    void SwapChart(ChartData *data);

    std::function<int()> cFunc;
    std::function<int()> pFunc;
};

#endif // CHARTBACKGROUND_H
