#include "ggraphicsview.h"
#include <QDebug>
#include <QMouseEvent>
#include <QTime>
#include <QtConcurrent>
#include <QThread>
#include <arena.h>

GGraphicsView::GGraphicsView()
{
    movep0 = new QTimer(this);
    movep1 = new QTimer(this);
    box = new Arena();
}

void GGraphicsView::setGScene(GGameScene *scene)
{
    this->setScene(scene);
    this->GScene = scene;
}

void GGraphicsView::startGame()
{
    setGScene(new GGameScene(box));
    GScene->setSceneRect(0,0,windowWidth,windowHeight);
    GScene->drawBoard();
}

void GGraphicsView::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat())
        return;
    int key = event->key();
    int affectedPlayer = -1;
    bool cw = false; //clockwise
    switch(key){
    case Qt::Key_D:
    case Qt::Key_W: affectedPlayer = 0; cw = true;  break;
    case Qt::Key_A:
    case Qt::Key_S: affectedPlayer = 0; cw = false; break;
    case Qt::Key_Left:
    case Qt::Key_Up: affectedPlayer= 1; cw = false; break;
    case Qt::Key_Right:
    case Qt::Key_Down: affectedPlayer=1;cw = true;  break;
    }
    if(affectedPlayer!=-1)
        clockWise[affectedPlayer] = cw;

    if(affectedPlayer == 0){
        setupTimer(movep0, this->GScene->p[0],cw);
    }else if(affectedPlayer == 1){
        setupTimer(movep1, this->GScene->p[1],cw);
    }
}

void GGraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat()){
        int key = event->key();
        int affectedPlayer = -1;
        bool cw = false;
        switch(key){
        case Qt::Key_D:
        case Qt::Key_W: affectedPlayer = 0; cw = true; break;
        case Qt::Key_A:
        case Qt::Key_S: affectedPlayer = 0; cw = false; break;
        case Qt::Key_Left:
        case Qt::Key_Up: affectedPlayer= 1; cw = false; break;
        case Qt::Key_Right:
        case Qt::Key_Down: affectedPlayer=1;cw = true; break;
            break;
        }
        if(clockWise[affectedPlayer] == cw){
            if(affectedPlayer == 0){
                movep0->stop();
            }else if(affectedPlayer==1){
                movep1->stop();
            }
        }
    }
}

void GGraphicsView::closeEvent(QCloseEvent * /*unused*/)
{
    GScene->ongoing = false;
    GScene->music->stop();
}

void GGraphicsView::setupTimer(QTimer* t, Player *p, bool cw)
{
    t->disconnect();
    t->stop();
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
