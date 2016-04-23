#include "ball.h"
#include <constants.h>
#include <qmath.h>
#include <QPainter>
#include <QGraphicsScene>
#include <GGameScene.h>
#include <QDebug>
#include <helper.h>
#include <QList>
#include <QThread>
#include <QtConcurrent>

Ball::Ball(GGameScene *parent)
{
    pos = new QPointF();
    this->parent = parent;
    this->p[0] = parent->p[0];
    this->p[1] = parent->p[1];
    pos->setX(windowWidth/2);
    pos->setY(windowHeight/2);
    radius = ballInitRadius;
    angle = randomInBound(0,5760);
    speed = ballInitSpeed;
    rekt = new QRectF();
    updateRect();
}

int Ball::getRadius()
{
    return radius;
}

QRectF Ball::boundingRect() const
{
    return *rekt;
}

void Ball::setrad(int r)
{
    radius = r;
    updateRect();
}

int arcTan(double x, double y){ //returns angle in 16ths of degree made by the point given
    int angleWithCenter = (int)(qAtan2(y,x)/M_PI*2880);
    if(angleWithCenter < 0){
        angleWithCenter+=5760;
    }
    return angleWithCenter;
}

void Ball::checkCollision()
{
    double distFromCenter = qSqrt(qPow(pos->x()-windowWidth/2,2)+qPow(pos->y()-windowHeight/2,2));

    if(distFromCenter < playerRadius-playerWidth-radius || distFromCenter > playerRadius+playerWidth+radius){
        //speed = 15-(double)distFromCenter/playerRadius*10;
        bouncing = false;
    }else{
        if(bouncing){
            return;
        }
        int angleWithCenter = arcTan(pos->x()-windowWidth/2,pos->y()-windowHeight/2);
        int p0diff = difference(angleWithCenter,p[0]->pos);
        int p1diff = difference(angleWithCenter,p[1]->pos);

        if(abs(p0diff) < p[0]->size+90){
            bounce(p[0],p0diff,angleWithCenter);
        }else if(abs(p1diff) < p[1]->size+90){
            bounce(p[1],p1diff,angleWithCenter);
        }else{
            bouncing = false;
        }
    }
    for(powerup* p: *parent->powerUps){
        if(distance(this->pos,p->pos()) < this->radius+p->rad()){
            parent->collectedPowerup(p);
        }
    }
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*unused*/, QWidget * /*unused*/)
{
    painter->setPen(this->pen);
    painter->setBrush(this->brush);
    painter->drawEllipse(pos->x()-radius,pos->y()-radius, radius*2,radius*2);
}

void Ball::bounce(Player* p, int pdiff, int angleWithCenter)
{
    angle = angleWithCenter+2880;
    normalize(angle);
    angle-=(((double)pdiff)/p->size*720);
    parent->mostRecent = p->playerNum;
    bouncing = true;
    QtConcurrent::run(this,&Ball::setBouncingToFalse);
}

void Ball::setBouncingToFalse()
{
    QThread::msleep(200);
    bouncing = false; //yes, this function serves a purpose.
}

QRectF *Ball::rect()
{
    return rekt;
}

void Ball::updateRect()
{
    rekt->setLeft(this->x()-radius);
    rekt->setTop(this->y()-radius);
    rekt->setWidth(radius*2);
    rekt->setHeight(radius*2);
}

void Ball::updatePos()
{
    pos->setX(pos->x()+speed*cos(angle*M_PI/2880));
    pos->setY(pos->y()+speed*sin(angle*M_PI/2880));
    updateRect();
    this->scene()->update();
    checkCollision();
}

void Ball::sizeUp()
{
    for(int i = 0; i < 5; i++){
        radius+=2;
        QThread::msleep(refreshInterval);
    }
}

void Ball::sizeDown()
{
    for(int i = 0; i < 5; i++){
        radius-=2;
        QThread::msleep(refreshInterval);
    }
}

void Ball::setPen(QPen pen)
{
    this->pen = pen;
}

void Ball::setBrush(QBrush brush)
{
    this->brush = brush;
}
