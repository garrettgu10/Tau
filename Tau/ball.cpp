#include "ball.h"
#include <constants.h>
#include <qmath.h>

Ball::Ball()
{
    pos->setX(windowWidth/2);
    pos->setY(windowHeight/2);
    radius = ballInitRadius;
}

int Ball::getRadius()
{
    return radius;
}

QRectF Ball::boundingRect() const
{
    return *rekt;
}

QRectF* Ball::rect(){
    return rekt;
}

void Ball::updateRect()
{
    rekt = new QRectF(this->x()-radius,this->y()-radius,radius*2,radius*2);
}

void Ball::updatePos()
{
    pos->setX(pos->x()+speed*cos(angle));
    pos->setY(pos->y()+speed*sin(angle));
}
