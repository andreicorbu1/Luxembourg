#include "Luxembourg.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Luxembourg w;
    w.setWindowState(Qt::WindowFullScreen);
    w.show();
    return a.exec();
}
