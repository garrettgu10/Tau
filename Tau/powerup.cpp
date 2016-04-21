#include "powerup.h"
#include <constants.h>
#include <helper.h>
#include <QPainter>
#include <ggraphicsscene.h>
#include <QDebug>
#include <QtConcurrent>

powerup::powerup(int id, GGraphicsScene *parent)
{
    this->parent = parent;
    this->id = id;
    t = static_cast<powerUpType>(qrand() % (int)powerUpType::NUM_POWERUPTYPES);
    position = new QPointF(randomInBound(windowWidth/2-arenaRadius/2,windowWidth/2+arenaRadius/2),
                      randomInBound(windowHeight/2-arenaRadius/2,windowHeight/2+arenaRadius/2));
    radius = powerUpRadius;
    rekt = new QRectF(position->x()-radius,position->y()-radius,radius*2,radius*2);
    enabled = false;
    ico = new QImage(":/ico/add.png");
    QtConcurrent::run(this,&powerup::fadeIn);
}

void powerup::enable()
{
    if(enabled){
        return;
    }
    switch(this->puptype()){
    case powerUpType::sizeUp: QtConcurrent::run((parent->b),&Ball::sizeUp); break;
    default: break;
    }
    QTimer* disabler = new QTimer();
    disabler->setSingleShot(true);
    QObject::connect(disabler,SIGNAL(timeout()),this,SLOT(disable()));
    disabler->start(10000);
    enabled = true;
}

void powerup::disable()
{
    if(!enabled)
        return;
    switch(this->puptype()){
    case powerUpType::sizeUp: QtConcurrent::run(parent->b,&Ball::sizeDown); break;
    default: break;
    }
}

void powerup::setPen(QPen pen)
{
    this->pen = pen;
}

void powerup::setBrush(QBrush brush)
{
    this->brush = brush;
}

QPointF* powerup::pos()
{
    return position;
}

powerUpType powerup::puptype()
{
    return t;
}

int powerup::rad()
{
    return radius;
}

void powerup::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(this->pen);
    painter->setBrush(this->brush);
    painter->setOpacity(opacity);
    painter->drawImage(QRectF(rect()), QImage(*ico));
}

QRectF powerup::rect()
{
    return *rekt;
}

QRectF powerup::boundingRect() const
{
    return *rekt;
}

void powerup::fadeIn()
{
    while(opacity < 1){
        opacity+=0.1;
        QThread::msleep(refreshInterval);
    }
}
