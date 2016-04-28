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
    QApplication a(argc, argv);
    GGraphicsView* view = new GGraphicsView();
    GGameScene* scene = new GGameScene();
    a.setKeyboardInputInterval(1600);
    view->setWindowTitle("Tau");
    view->setRenderHint(QPainter::Antialiasing);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setGScene(scene);
    view->setFixedSize(windowWidth,windowHeight);
    scene->setSceneRect(0,0,windowWidth,windowHeight);
    view->setVisible(true);
    scene->updateGradBackground();
    scene->drawBoard();

    return a.exec();
}
