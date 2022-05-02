#include "SelectedAtom.h"
#include "ui_SelectedAtom.h"
#include <QDebug>
#include <QScrollBar>
#include <QLineEdit>

SelectedAtom::SelectedAtom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectedAtom)
{
    ui->setupUi(this);
    mListWidget = new QListWidget();
    mEdit = new QLineEdit();
    for (int i = 0; i < 256; ++i) {
        QListWidgetItem *item = new QListWidgetItem(mListWidget);
        mItems.push_back(item);
        QCheckBox *box = new QCheckBox();
        connect(box, &QCheckBox::stateChanged, this, [box, this](int f){
            if (f == Qt::Checked) {
                if (!mSelectedList.contains(box->text())) {
                    mSelectedList.push_back(box->text());
                }
            } else if (f == Qt::Unchecked){
                if (mSelectedList.contains(box->text())) {
                    mSelectedList.removeOne(box->text());
                }
            }
            QString str;
            for (int i = 0; i < mSelectedList.size(); ++i) {
                str += mSelectedList[i];
                if (i != mSelectedList.size() - 1) {
                    str += ",";
                }
            }
            mEdit->setText(str);
        });
        mListWidget->setItemWidget(item, box);
        mBoxs.push_back(box);
        box->setText(QString::number(i));
    }
    ui->comboBox->setView(mListWidget);
    ui->comboBox->setModel(mListWidget->model());
    ui->comboBox->setLineEdit(mEdit);
    mEdit->setReadOnly(true);
}

SelectedAtom::~SelectedAtom()
{
    qDeleteAll(mBoxs);
    qDeleteAll(mItems);
    delete mListWidget;
    delete mEdit;
    delete ui;
}

QStringList SelectedAtom::GetSelected()
{
    return mSelectedList;
}

void SelectedAtom::on_pushButton_2_clicked()
{
    QDialog::accept();
}

void SelectedAtom::on_pushButton_clicked()
{
    QDialog::reject();
}

AtomComboBox::AtomComboBox(QWidget *parent) : QComboBox(parent)
{

}

AtomComboBox::~AtomComboBox()
{

}

void AtomComboBox::hidePopup()
{
    QListWidget *uu = qobject_cast<QListWidget*>(this->view());
    QModelIndex index = model()->index(0, 0);
    uu->setCurrentIndex(index);
    QComboBox::hidePopup();
}

void AtomComboBox::showPopup()
{

    QComboBox::showPopup();
}

void SelectedAtom::on_pushButton_3_clicked()
{
    for (QCheckBox *cb : mBoxs) {
        cb->setCheckState(Qt::Unchecked);
    }
}
