#include <QApplication>
#include <QMainWindow>
#include "QOSGWidget.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QMainWindow* w = new QMainWindow;
    QOSGWidget *osgWidget = new QOSGWidget(1, 1, w);
    w->setCentralWidget(osgWidget);
    w->show();
    return app.exec();
}