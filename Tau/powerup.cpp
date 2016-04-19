#include "powerup.h"
#include <constants.h>
#include <helper.h>
#include <QPainter>

powerup::powerup()
{
    powerUpType foo = static_cast<powerUpType>(qrand() % (int)powerUpType::NUM_POWERUPTYPES);
    position = new QPointF(randomInBound(windowWidth/2-arenaRadius/2,windowWidth/2+arenaRadius/2),
                      randomInBound(windowHeight/2-arenaRadius/2,windowHeight/2+arenaRadius/2));
    rekt = new QRectF(this->x()-radius,this->y()-radius,radius*2,radius*2);
    radius = powerUpRadius;
}

void powerup::enable()
{

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

void powerup::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(this->pen);
    painter->setBrush(this->brush);
    painter->drawEllipse(position->x()-radius,position->y()-radius, radius*2,radius*2);
}

QRectF powerup::rect()
{
    return *rekt;
}

QRectF powerup::boundingRect() const
{
    return *rekt;
}
