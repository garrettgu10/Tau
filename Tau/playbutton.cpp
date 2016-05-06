#include "playbutton.h"

playButton::playButton(int size)
{
    angle = 0;
    this->size = size;
    this->permSize = size;
    this->setPoints(size);
}

QRectF playButton::boundingRect() const
{
    return QRectF(windowWidth/2-size,windowHeight/2-size,size*2,size*2);
}

void playButton::setBrush(QBrush *brush)
{
    this->brush = brush;
}

void playButton::setPen(QPen *pen)
{
    this->pen = pen;
}

void playButton::incrementAngle()
{
    angle+=2;
}

void playButton::setSize(int size)
{
    this->size = size;
    this->setPoints(size);
}

int playButton::getSize()
{
    return size;
}

void playButton::pulse()
{
    setSize(size+10);
}

void playButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setOpacity(opacity);
    painter->setBrush(*brush);
    painter->setPen(*pen);
    painter->translate(windowWidth/2,windowHeight/2);
    painter->rotate(angle);
    painter->drawPolygon(points,3);
}

void playButton::setPoints(int size)
{
    points[0] = QPointF(size,0);
    points[1] = QPointF(-size/2,size*sqrt(3)/2);
    points[2] = QPointF(-size/2,-size*sqrt(3)/2);
}
