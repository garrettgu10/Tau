#include "ggraphicsview.h"
#include <QDebug>
#include <QMouseEvent>

GGraphicsView::GGraphicsView()
{
    movep1 = new QTimer(this);
    movep2 = new QTimer(this);
}

void GGraphicsView::setGScene(GGameScene *scene)
{
    this->setScene(scene);
    this->GScene = scene;
}

void GGraphicsView::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    int affectedPlayer = -1;
    bool cw = false; //clockwise
    switch(key){
    case Qt::Key_W: affectedPlayer = 1; cw = true;  break;
    case Qt::Key_S: affectedPlayer = 1; cw = false; break;
    case Qt::Key_Up: affectedPlayer= 2; cw = false; break;
    case Qt::Key_Down: affectedPlayer=2;cw = true;  break;
    }
    if(affectedPlayer == 1 && !(movep1->isActive())){
        setupTimer(movep1, this->GScene->p1,cw);
    }else if(affectedPlayer == 2 && !(movep2->isActive())){
        setupTimer(movep2, this->GScene->p2,cw);
    }
}

void GGraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    int key = event->key();
    int affectedPlayer = -1;
    switch(key){
    case Qt::Key_W: affectedPlayer = 1; break;
    case Qt::Key_S: affectedPlayer = 1; break;
    case Qt::Key_Up: affectedPlayer= 2; break;
    case Qt::Key_Down: affectedPlayer=2;break;
    }
    if(affectedPlayer == 1){
        movep1->stop();
    }else if(affectedPlayer==2){
        movep2->stop();
    }

}

void GGraphicsView::closeEvent(QCloseEvent *event)
{
    GScene->ongoing = false;
}

void GGraphicsView::setupTimer(QTimer* t, Player *p, bool cw)
{
    t->disconnect();
    if(cw){
        QObject::connect(t,SIGNAL(timeout()),p,SLOT(moveClockwise()));
    }else{
        QObject::connect(t,SIGNAL(timeout()),p,SLOT(moveCClockwise()));
    }
    t->start(refreshInterval);
}

void GGraphicsView::mousePressEvent(QMouseEvent *event)
{
    qDebug() << event->x();
    qDebug() << event->y();
}
