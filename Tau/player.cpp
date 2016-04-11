#include "player.h"
#include <QRectF>
#include <ggraphicsscene.h>
#include <QPainter>
#include <constants.h>
#include <QPen>

Player::Player(double pos, double size)
{
    this->pos = pos;
    this->size = size;
    this->rekt = new QRectF(QPointF(windowWidth/2-playerRadius,windowHeight/2-playerRadius),QSizeF((playerRadius)*2,(playerRadius)*2));
}

int Player::startAngle(){
    return pos-size;
}

int Player::spanAngle(){
    return size*2;
}

QRectF* Player::rect(){
    return rekt;
}

void Player::setBrush(QBrush brush)
{
    this->brush = brush;
}

QRectF Player::boundingRect() const
{
    return *rekt;
}

void Player::setPen(QPen pen){
    this->pen = pen;
}

void Player::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) {
    painter->setPen(this->pen);
    painter->setBrush(this->brush);
    painter->drawArc(*rect(), startAngle(), spanAngle());
}
