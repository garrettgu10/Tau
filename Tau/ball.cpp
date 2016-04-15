#include "ball.h"
#include <constants.h>
#include <qmath.h>
#include <QPainter>

Ball::Ball()
{
    pos = new QPointF();
    pos->setX(windowWidth/2);
    pos->setY(windowHeight/2);
    radius = ballInitRadius;
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
    pos->setX(pos->x()+speed*cos(angle));
    pos->setY(pos->y()+speed*sin(angle));
}

void Ball::setPen(QPen pen)
{
    this->pen = pen;
}

void Ball::setBrush(QBrush brush)
{
    this->brush = brush;
}
