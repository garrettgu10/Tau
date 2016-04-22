#include "powerup.h"
#include <constants.h>
#include <helper.h>
#include <QPainter>
#include <ggamescene.h>
#include <QDebug>
#include <QtConcurrent>

powerup::powerup(int id, GGameScene *parent)
{
    this->parent = parent;
    this->id = id;
    t = static_cast<powerUpType>(qrand() % (int)powerUpType::NUM_POWERUPTYPES);
    position = new QPointF(randomInBound(windowWidth/2-arenaRadius/2,windowWidth/2+arenaRadius/2),
                      randomInBound(windowHeight/2-arenaRadius/2,windowHeight/2+arenaRadius/2));
    radius = powerUpRadius;
    rekt = new QRectF(position->x()-radius,position->y()-radius,radius*2,radius*2);
    enabled = false;
    QtConcurrent::run(this,&powerup::fadeIn);
    QtConcurrent::run(this,&powerup::keepRotating);
}

void powerup::enable()
{
    if(enabled){
        return;
    }
    affectedPlayer = parent->p[parent->mostRecent];
    switch(this->puptype()){
    case powerUpType::ballSizeUp: QtConcurrent::run((parent->b),&Ball::sizeUp); break;
    case powerUpType::paddleSizeUp: QtConcurrent::run(affectedPlayer,&Player::sizeUp); break;
    case powerUpType::paddleSizeDown: QtConcurrent::run(affectedPlayer,&Player::sizeDown); break;
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
    case powerUpType::ballSizeUp: QtConcurrent::run(parent->b,&Ball::sizeDown); break;
    case powerUpType::paddleSizeUp: QtConcurrent::run(affectedPlayer,&Player::sizeDown); break;
    case powerUpType::paddleSizeDown: QtConcurrent::run(affectedPlayer,&Player::sizeUp); break;
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
    if(!enabled){
        painter->setPen(this->pen);
        painter->setBrush(this->brush);
        painter->setOpacity(opacity);
        painter->translate(position->x(),position->y());
        painter->rotate(angle);
        painter->drawImage(QRectF(-radius,-radius,radius*2,radius*2), QImage(icos[(int)t]));
    }
}

QRectF powerup::rect()
{
    return *rekt;
}

QRectF powerup::boundingRect() const
{
    return *rekt;
}

void powerup::keepRotating()
{
    while(!enabled && parent->ongoing){
        angle+=3;
        QThread::msleep(refreshInterval);
    }
}

void powerup::fadeIn()
{
    while(opacity < 1){
        opacity+=0.1;
        QThread::msleep(refreshInterval);
    }
}
