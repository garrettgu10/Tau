#include "mainwindow.h"
#include <QApplication>
#include <QThread>
#include <QTimer>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
