#include "ball.h"
#include <constants.h>
#include <qmath.h>
#include <QPainter>
#include <QGraphicsScene>
#include <GGraphicsScene.h>
#include <QDebug>
#include <helper.h>


Ball::Ball(Player *p1, Player *p2)
{
    pos = new QPointF();
    this->p1 = p1;
    this->p2 = p2;
    pos->setX(windowWidth/2);
    pos->setY(windowHeight/2);
    radius = ballInitRadius;
    angle = randomInBound(0,5760);
    speed = ballInitSpeed;
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

int arcTan(double x, double y){ //returns angle in 16ths of degree made by the point given
    int angleWithCenter = (int)(qAtan2(y,x)/M_PI*2880);
    if(angleWithCenter < 0){
        angleWithCenter+=5760;
    }
    return angleWithCenter;
}

void Ball::collision()
{
    double distFromCenter = qSqrt(qPow(pos->x()-windowWidth/2,2)+qPow(pos->y()-windowHeight/2,2));

    if(distFromCenter < playerRadius-playerWidth-radius || distFromCenter > arenaRadius+radius){
        //speed = 15-(double)distFromCenter/playerRadius*10;
        bouncing = false;
    }else{
        if(bouncing){
            return;
        }
        int angleWithCenter = arcTan(pos->x()-windowWidth/2,pos->y()-windowHeight/2);
        int p1diff = difference(angleWithCenter,p1->pos);
        int p2diff = difference(angleWithCenter,p2->pos);

        if(abs(p1diff) < p1->size+90){
            angle = angleWithCenter+2880;
            normalize(angle);
            angle-=(((double)p1diff)/p1->size*720);
            bouncing = true;
        }else if(abs(p2diff) < p2->size+90){
            angle = angleWithCenter+2880;
            normalize(angle);
            angle-=(((double)p2diff)/p2->size*720);
            bouncing = true;
        }
    }
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(this->pen);
    painter->setBrush(this->brush);
    painter->drawEllipse(pos->x()-radius,pos->y()-radius, radius*2,radius*2);
}

QRectF* Ball::rect()
{
    return rekt;
}

void Ball::updateRect()
{
    rekt = new QRectF(this->x()-radius,this->y()-radius,radius*2,radius*2);
}

void Ball::updatePos()
{
    pos->setX(pos->x()+speed*cos(angle*M_PI/2880));
    pos->setY(pos->y()+speed*sin(angle*M_PI/2880));
    updateRect();
    this->scene()->update();
    collision();
}

void Ball::setPen(QPen pen)
{
    this->pen = pen;
}

void Ball::setBrush(QBrush brush)
{
    this->brush = brush;
}
