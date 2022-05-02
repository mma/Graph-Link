#ifndef SELECTEDATOM_H
#define SELECTEDATOM_H

#include <QDialog>
#include <QListWidget>
#include <QCheckBox>
#include <QComboBox>

namespace Ui {
class SelectedAtom;
}

class AtomComboBox : public QComboBox
{
public:
    AtomComboBox(QWidget *parent = nullptr);
    ~AtomComboBox();

protected:
    void hidePopup() override;
    void showPopup() override;
};

class SelectedAtom : public QDialog
{
    Q_OBJECT

public:
    explicit SelectedAtom(QWidget *parent = nullptr);
    ~SelectedAtom();
    QStringList GetSelected();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::SelectedAtom *ui;
    QListWidget *mListWidget;
    QVector<QCheckBox *> mBoxs;
    QVector<QListWidgetItem *> mItems;
    QLineEdit *mEdit;
    QStringList mSelectedList;
};

#endif // SELECTEDATOM_H
