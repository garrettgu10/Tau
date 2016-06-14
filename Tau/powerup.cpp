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
    pupType = static_cast<powerUpType>(qrand() % (int)powerUpType::NUM_POWERUPTYPES);
    position = new QPointF(randomInBound(windowWidth/2-arenaRadius/2,windowWidth/2+arenaRadius/2),
                      randomInBound(windowHeight/2-arenaRadius/2,windowHeight/2+arenaRadius/2));
    radius = powerUpRadius;
    rekt = new QRectF(position->x()-radius,position->y()-radius,radius*2,radius*2);
    enabled = false;
    QtConcurrent::run(this,&powerup::fadeIn);
    QTimer* rotator = new QTimer();
    QObject::connect(rotator,SIGNAL(timeout()),this,SLOT(rotate()));
    rotator->start(defaultRefreshInterval);

    this->setCacheMode(QGraphicsItem::ItemCoordinateCache);
    this->setTransformOriginPoint(QPointF(*position));
}

void powerup::enable()
{
    if(enabled){
        return;
    }
    if(pupType==powerUpType::random){
        while(pupType==powerUpType::random || pupType==powerUpType::arrow){
            pupType = static_cast<powerUpType>(qrand() % (int)powerUpType::NUM_POWERUPTYPES);
        }
    }
    affectedPlayer = parent->p[parent->mostRecent];
    switch(this->puptype()){
    case powerUpType::ballSizeUp: QtConcurrent::run((parent->ball),&Ball::sizeUp); parent->sizeUp->play(); break;
    case powerUpType::paddleSizeUp: QtConcurrent::run(affectedPlayer,&Player::sizeUp); parent->sizeUp->play(); break;
    case powerUpType::paddleSizeDown: QtConcurrent::run(affectedPlayer,&Player::sizeDown); parent->sizeDown->play(); break;
    case powerUpType::arrow: parent->ball->setAngle((int)(this->angle*16)); break;
    case powerUpType::warp: parent->ball->warper->start(500); break;
    case powerUpType::lightning: parent->ball->setSpeed(parent->ball->getSpeed()+3); break;
    case powerUpType::wobble: parent->ball->startWobble(); break;
    case powerUpType::ghost: parent->ball->startGhost(); break;
    case powerUpType::snail: if(!parent->ball->setSpeed(parent->ball->getSpeed()-3)){ disabled = true; } break;
    default: break;
    }
    enabled = true;
    parent->overlappingPups[(int)pupType]++;
    QTimer::singleShot(powerUpEnabledTime,Qt::PreciseTimer,this,SLOT(disable()));
}

void powerup::disable()
{
    if(disabled){
        return;
    }
    if(!enabled){
        return;
    }
    parent->overlappingPups[(int)pupType]--;
    if(powerupExtendable[(int)pupType] && parent->overlappingPups[(int)pupType]!=0){
        disabled = true;
        return;
    }
    switch(this->puptype()){
    case powerUpType::ballSizeUp: QtConcurrent::run(parent->ball,&Ball::sizeDown); parent->sizeDown->play(); break;
    case powerUpType::paddleSizeUp: QtConcurrent::run(affectedPlayer,&Player::sizeDown); parent->sizeDown->play(); break;
    case powerUpType::paddleSizeDown: QtConcurrent::run(affectedPlayer,&Player::sizeUp); parent->sizeUp->play(); break;
    case powerUpType::arrow: /*do nothing*/ break;
    case powerUpType::warp: parent->ball->warper->stop(); break;
    case powerUpType::lightning: parent->ball->setSpeed(parent->ball->getSpeed()-3); break;
    case powerUpType::wobble: parent->ball->wobbler->stop(); parent->ball->setAngle(parent->ball->getAngle()); parent->ball->wobbling = false; break;
    case powerUpType::ghost: parent->ball->stopGhost(); break;
    case powerUpType::snail: parent->ball->setSpeed(parent->ball->getSpeed()+3); break;
    default: break;
    }
    disabled = true;
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
    return pupType;
}

int powerup::rad()
{
    return radius;
}

void powerup::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*unused*/, QWidget * /*unused*/)
{
    if(!enabled){
        painter->setPen(this->pen);
        painter->setBrush(this->brush);
        painter->setOpacity(opacity);
        painter->translate(position->x(),position->y());
        painter->drawImage(QRectF(-radius,-radius,radius*2,radius*2), QImage(icos[(int)pupType]));
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

void powerup::rotate()
{
    angle+=3;
    this->setRotation(angle);
}

void powerup::fadeIn()
{
    while(opacity < 1){
        opacity+=0.2;
        this->update();
        QThread::msleep(defaultRefreshInterval);
    }
}
