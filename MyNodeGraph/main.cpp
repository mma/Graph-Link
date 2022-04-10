#include "Widget.h"

#include <QApplication>
// 在 windows11上 右下角不是圆角，不知道是不是bug
QString qss = "QMenu {\
     background-color : rgb(255,255,255);\
     padding : 5px;\
     margin : 5px;\
     border : 1px solid gray;\
     border-radius:10px;\
    }\
    QMenu::item {\
        font-size:10pt;\
        color: rgb(0,0,0);\
        background-color: transparent;\
        padding: 8px 25px 6px 10px;\
        margin: 4px 1px;\
    }\
    QMenu::item:selected {\
        background-color : lightblue;\
        border-radius:5px;\
    }\
    QMenu::icon:checked {\
        background: rgb(253,253,254);\
        position: absolute;\
        top: 1px;\
        right: 1px;\
        bottom: 1px;\
        left: 1px;\
    }\
    QMenu::icon:checked:selected {\
        background-color : rgb(236,236,237);\
    }\
    QMenu::separator {\
        height: 2px;\
        background: rgb(235,235,236);\
        margin-left: 5px;\
        margin-right: 5px;\
    }\
";
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet(qss);
    Widget w;
    w.show();
    return a.exec();
}
