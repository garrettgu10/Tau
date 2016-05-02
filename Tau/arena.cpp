#include "arena.h"
#include <QPainter>
#include <QGraphicsEllipseItem>

Arena::Arena()
{
    grad->setColorAt(0,QColor(0,0,0,0));
    grad->setColorAt(1,QColor::fromRgb(0,0,0,255));
}

void Arena::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(QBrush(*grad));
    painter->setPen(*clear);
    painter->drawRect(0,0,windowWidth,windowHeight);
    painter->setPen(*redPen);
    painter->setBrush(this->brush());
    painter->drawArc(rect(), -1440, 2880);
    painter->setPen(*bluePen);
    painter->drawArc(rect(),1440,2880);
}

void Arena::setPen(const QPen &pen)
{
    bluePen = new QPen(pen);
    bluePen->setColor(QColor::fromRgb(165,165,255));
    redPen = new QPen(pen);
    redPen->setColor(QColor::fromRgb(255,165,165));
}

void Arena::setRadius(int rad)
{
    this->radius = rad;
    this->setRect(windowWidth/2-rad,windowHeight/2-rad,rad*2,rad*2);
}

void Arena::pulse()
{
    grad->setColorAt(0,QColor::fromRgb(randomInBound(50,150),randomInBound(50,150),randomInBound(50,150),255));

    setRadius(arenaRadius+10);
}
