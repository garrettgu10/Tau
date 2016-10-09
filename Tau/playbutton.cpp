#include "playbutton.h"

playButton::playButton(int size)
{
    this->setTransformOriginPoint(windowWidth/2,windowHeight/2);
    angle = 0;
    this->size = size;
    this->permSize = size;
    this->setPoints(size);

    this->setCacheMode(QGraphicsItem::ItemCoordinateCache);
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
    this->setRotation(angle);
}

void playButton::setSize(int size)
{
    this->size = size;
    if(pulsing){
        this->setScale((double)size/playButtonSize);
    }else{
        setPoints(size);
    }
    this->update();

}

int playButton::getSize()
{
    return size;
}

void playButton::pulse()
{
    setSize(playButtonSize+10);
}

void playButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setOpacity(opacity);
    painter->setBrush(*brush);
    painter->setPen(*pen);
    painter->translate(windowWidth/2,windowHeight/2);
    painter->drawPolygon(points,3);
}

void playButton::setPoints(int size)
{
    points[0] = QPointF(size,0);
    points[1] = QPointF(-size/2,size*sqrt(3)/2);
    points[2] = QPointF(-size/2,-size*sqrt(3)/2);
}
