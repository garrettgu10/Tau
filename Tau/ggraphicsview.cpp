#include "ggraphicsview.h"
#include <QDebug>
#include <QMouseEvent>

GGraphicsView::GGraphicsView()
{

}

void GGraphicsView::setGScene(GGraphicsScene *scene)
{
    this->setScene(scene);
    this->GScene = scene;
}

void GGraphicsView::keyPressEvent(QKeyEvent *event){
    int key = event->key();
    switch(key){
    case Qt::Key_W: this->GScene->p1->move(-180); break;
    case Qt::Key_S: this->GScene->p1->move(180); break;
    case Qt::Key_Up: this->GScene->p2->move(180); break;
    case Qt::Key_Down: this->GScene->p2->move(-180); break;
    }
}

void GGraphicsView::mousePressEvent(QMouseEvent *event)
{
    qDebug() << event->x();
    qDebug() << event->y();
}
