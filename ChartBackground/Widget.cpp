#include "Widget.h"
#include "ui_Widget.h"
#include <QScrollBar>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mWidget = std::make_shared<ChartBackground>();
    ui->verticalLayout_2->addWidget(mWidget.get());
    ui->verticalLayout_2->addStretch();
    auto cur = std::bind(&Widget::GetCurrent, this);
    auto page = std::bind(&Widget::GetPageStep,this);
    mWidget->RegisterCurrent(cur);
    mWidget->RegisterPageStep(page);
}

Widget::~Widget()
{
    delete ui;
}

int Widget::GetCurrent()
{
    return ui->scrollArea->verticalScrollBar()->value();
}

int Widget::GetPageStep()
{
    return ui->scrollArea->verticalScrollBar()->pageStep();
}

