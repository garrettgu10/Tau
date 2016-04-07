#include <QApplication>
#include <QTimer>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsView* view = new QGraphicsView();
    view->setScene(scene);
    QGraphicsRectItem* rect = new QGraphicsRectItem();
    rect->setRect(0,0,100,100);
    scene->addItem(rect);
    view->setVisible(true);
    return a.exec();
}
