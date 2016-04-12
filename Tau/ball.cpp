#include "ball.h"
#include <constants.h>

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

QRectF Ball::boundingRect()
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
