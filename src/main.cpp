#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font = a.font();
    font.setPointSize(8);
    a.setFont(font);
    a.setStyle("fusion");

    MainWindow w;
    w.show();
    return a.exec();
}
