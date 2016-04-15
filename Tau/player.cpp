#include "player.h"
#include <QRectF>
#include <ggraphicsscene.h>
#include <QPainter>
#include <constants.h>
#include <QPen>
#include <QDebug>

Player::Player(double pos, double size,int playerNum)
{
    this->playerNum = playerNum;
    this->pos = pos;
    this->size = size;
    this->rekt = new QRectF(QPointF(windowWidth/2-playerRadius,windowHeight/2-playerRadius),QSizeF((playerRadius)*2,(playerRadius)*2));
}

int Player::startAngle()
{
    return pos-size;
}

int Player::spanAngle()
{
    return size*2;
}

QRectF* Player::rect()
{
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

void Player::move(int dtheta)
{
    int newPos = this->pos+dtheta;
    if(newPos+size <=4320-2880*playerNum && newPos-size >=1440-2880*playerNum){
        this->pos+=dtheta;
        this->scene()->update();
    }
}

void Player::moveClockwise()
{
    move(-90);
}

void Player::moveCClockwise()
{
    move(90);
}

void Player::setPen(QPen pen){
    this->pen = pen;
}

void Player::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->setPen(this->pen);
    painter->setBrush(this->brush);
    painter->drawArc(*rect(), startAngle(), spanAngle());
}
