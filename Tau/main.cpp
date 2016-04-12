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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GGraphicsScene* scene = new GGraphicsScene();
    GGraphicsView* view = new GGraphicsView();
    view->setRenderHint(QPainter::Antialiasing);
    view->setGScene(scene);
    view->setFixedSize(1425,750);
    scene->setSceneRect(0,0,1425,750);
    view->setVisible(true);
    scene->drawGradBackground();
    scene->drawBoard();

    return a.exec();
}
