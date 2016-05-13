#include <QApplication>
#include <QTimer>
#include <QObject>
#include <QGraphicsScene>
#include <GGraphicsView.h>
#include <QGraphicsRectItem>
#include <QPen>
#include "ggamescene.h"
#include "ggraphicsview.h"
#include <QPainter>
#include <helper.h>
#include <constants.h>
#include <QWindow>
#include <QMediaPlayer>
#include <QThread>
#include <QDebug>

int main(int argc, char *argv[])
{
    seedRandomFunction();

    QCoreApplication::setOrganizationName("GarrettGu");
    QCoreApplication::setOrganizationDomain("qzvx.org");
    QCoreApplication::setApplicationName("Tau");

    QApplication a(argc, argv);
    GGraphicsView* view = new GGraphicsView();
    a.setKeyboardInputInterval(1600);
    view->setWindowTitle("\u03C4");
    view->setRenderHint(QPainter::Antialiasing);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(windowWidth,windowHeight);
    view->setVisible(true);

    return a.exec();
}
