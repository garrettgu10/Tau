#include <QApplication>
#include <QTimer>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QPen>
#include "ggraphicsscene.h"
#include "ggraphicsview.h"
#include <QPainter>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GGraphicsScene* scene = new GGraphicsScene();
    QGraphicsView* view = new GGraphicsView();
    view->setRenderHint(QPainter::Antialiasing);
    view->setScene(scene);
    view->setFixedSize(1425,750);
    scene->setSceneRect(0,0,1425,750);
    view->setVisible(true);
    scene->drawGradBackground();
    scene->drawBoard();

    return a.exec();
}
