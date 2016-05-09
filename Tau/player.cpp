#include "player.h"
#include <QRectF>
#include <ggamescene.h>
#include <QPainter>
#include <constants.h>
#include <QPen>
#include <QDebug>
#include <QThread>
#include <QtConcurrent>

Player::Player(double pos, double size,int playerNum)
{
    this->playerNum = playerNum;
    this->pos = pos;
    this->size = size;
    this->rekt = new QRectF(QPointF(windowWidth/2-playerRadius,windowHeight/2-playerRadius),QSizeF((playerRadius)*2,(playerRadius)*2));
}

int Player::startAngle()
{
    return pos+size;
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
        //this->scene()->update();
    }
}

void Player::sizeUp()
{
    for(int i = 0; i < 4; i++){
        this->size+=11;
        QThread::msleep(refreshInterval);
    }
    if(this->pos+this->size > 4320-2880*playerNum){
        this->moveCClockwise();
    }
    if(this->pos-this->size < 1440-2880*playerNum){
        this->moveClockwise();
    }
}

void Player::sizeDown()
{
    for(int i = 0; i < 4; i++){
        this->size-=11;
        QThread::msleep(refreshInterval);
    }
}

void Player::fadeIn()
{
    for(int i = 0; i < 10; i++){
        opacity+=0.10;
        QThread::msleep(refreshInterval);
    }
}

void Player::fadeOut()
{
    for(int i = 0; i < 10; i++){
        opacity-=0.10;
        QThread::msleep(refreshInterval);
    }
}

void Player::moveClockwise()
{
    move(88);
}

void Player::moveCClockwise()
{
    move(-88);
}

void Player::setPen(QPen pen){
    this->pen = pen;
}

void Player::paint ( QPainter * painter, const QStyleOptionGraphicsItem* /*unused*/, QWidget* /*unused*/)
{
    painter->setOpacity(opacity);
    painter->setPen(this->pen);
    painter->setBrush(this->brush);
    painter->drawArc(*rect(), -startAngle(), spanAngle());
}
