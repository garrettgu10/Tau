#include <QApplication>
#include <QTimer>
#include <QObject>
#include <QGraphicsScene>
#include <GGraphicsView.h>
#include <QGraphicsRectItem>
#include <QPen>
#include "ggraphicsscene.h"
#include "ggraphicsview.h"
#include <QPainter>
#include <helper.h>
#include <constants.h>

int main(int argc, char *argv[])
{
    seedRandomFunction();
    QApplication a(argc, argv);
    GGraphicsScene* scene = new GGraphicsScene();
    GGraphicsView* view = new GGraphicsView();
    //view->setRenderHint(QPainter::Antialiasing);
    view->setGScene(scene);
    view->setFixedSize(windowWidth,windowHeight);
    scene->setSceneRect(0,0,windowWidth,windowHeight);
    view->setVisible(true);
    scene->drawGradBackground();
    scene->drawBoard();

    return a.exec();
}
