#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.setWindowTitle("机器人手眼对位系统");
	w.show();
    //w.show();
    return a.exec();
}
