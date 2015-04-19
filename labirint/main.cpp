#include "mainwidget.h"
#include <QApplication>

#include <QTime>

int main(int argc, char *argv[])
{
    srand(QTime::currentTime().msecsSinceStartOfDay());

    QApplication a(argc, argv);
    MainWidget w;
    w.show();

    return a.exec();
}
