#include "mainwindow.h"
#include <QApplication>
#include <QStyle>
#include <QStyleFactory>
#include <QStyle>
#include <QDebug>
#include <QResource>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QResource::registerResource("application.qrc");

    MainWindow w;
    w.show();

    return a.exec();
}


