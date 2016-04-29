#include "ball.h"
#include <constants.h>
#include <qmath.h>
#include <QPainter>
#include <QGraphicsScene>
#include <GGameScene.h>
#include <QDebug>
#include <helper.h>
#include <QList>
#include <QThread>
#include <QtConcurrent>

Ball::Ball(GGameScene *parent)
{   
    pos = new QPointF();
    this->parent = parent;
    this->p[0] = parent->p[0];
    this->p[1] = parent->p[1];
    pos->setX(windowWidth/2);
    pos->setY(windowHeight/2);
    radius = ballInitRadius;
    angle = randomInBound(0,5760);
    setSpeed(ballInitSpeed);
    rekt = new QRectF();
    updateRect();

    warper = new QTimer();
    QObject::connect(warper,SIGNAL(timeout()),this,SLOT(warpToggleSpeeds()));
    wobbler = new QTimer();
    QObject::connect(wobbler,SIGNAL(timeout()),this,SLOT(wobble()));

    collisionSound = new QSoundEffect();
    collisionSound->setVolume(0);
    collisionSound->setSource(QUrl::fromLocalFile(":/sound/collide.wav"));
    setup();
}

int Ball::getRadius()
{
    return radius;
}

QRectF Ball::boundingRect() const
{
    return *rekt;
}

void Ball::setrad(int r)
{
    radius = r;
    updateRect();
}

void Ball::setAngle(int angle)
{
    this->angle = angle;
}

void Ball::explode()
{
    speed = 0;
    for(int i = 0; i < 10; i++){
        opacity-=0.1;
        radius+=5;
        QThread::msleep(refreshInterval);
    }
}

void Ball::startGhost()
{
    if(ghoster == NULL || !ghoster->isActive()){
        opacity = 1.0;
        goingBrighter = false;
        ghoster = new QTimer();
        QObject::connect(ghoster, SIGNAL(timeout()),this,SLOT(ghostUpdate()));
        ghoster->start(refreshInterval);
    }
}

void Ball::stopGhost()
{
    ghoster->stop();
    opacity = 1.0;
}

double Ball::getSpeed()
{
    return speed;
}

void Ball::setSpeed(double newSpeed)
{
    if(newSpeed>=0){
        speed = newSpeed;
    }
}

void Ball::setup()
{
    this->setSpeed(0);
    this->pos->setX(windowWidth/2);
    this->pos->setY(windowHeight/2);
    this->opacity = 1.0;
    this->radius = ballInitRadius;
    this->disabled = false;
    this->warpSpedUp = false;
    QtConcurrent::run(this,&Ball::initSpin);
}

void Ball::wobble()
{
    int quadrantNum = (angle%5760)/1440; //0 to 3
    angle = randomInBound(quadrantNum*1440,(quadrantNum+1)*1440);
}

void Ball::warpToggleSpeeds()
{
    if(warpSpedUp){
        setSpeed(speed-2);
        warpSpedUp = false;
    }else{
        setSpeed(speed+2);
        warpSpedUp = true;
    }
}

int arcTan(double x, double y){ //returns angle in 16ths of degree made by the point given
    int angleWithCenter = (int)(qAtan2(y,x)/M_PI*2880);
    if(angleWithCenter < 0){
        angleWithCenter+=5760;
    }
    return angleWithCenter;
}

void Ball::checkCollision()
{
    if(disabled || speed == 0){
        return;
    }
    double distFromCenter = qSqrt(qPow(pos->x()-windowWidth/2,2)+qPow(pos->y()-windowHeight/2,2));

    if(distFromCenter < playerRadius-playerWidth-radius){
        //speed = 15-(double)distFromCenter/playerRadius*10;
        bouncing = false;
    }else if(distFromCenter > playerRadius+playerWidth-radius){
        bouncing = false;
        this->parent->gameOver();
    }else{
        if(bouncing){
            return;
        }
        int angleWithCenter = arcTan(pos->x()-windowWidth/2,pos->y()-windowHeight/2);
        int p0diff = difference(angleWithCenter,p[0]->pos);
        int p1diff = difference(angleWithCenter,p[1]->pos);

        if(abs(p0diff) < p[0]->size+90){
            bounce(p[0],p0diff,angleWithCenter);
        }else if(abs(p1diff) < p[1]->size+90){
            bounce(p[1],p1diff,angleWithCenter);
        }else{
            bouncing = false;
        }
    }
    for(powerup* p: *parent->powerUps){
        if(!p->enabled){
            if(distance(this->pos,p->pos()) < this->radius+p->rad()){
                parent->collectedPowerup(p);
            }
        }
    }
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*unused*/, QWidget * /*unused*/)
{
    painter->setPen(this->pen);
    painter->setBrush(this->brush);
    painter->setOpacity(opacity);
    painter->drawEllipse(pos->x()-radius,pos->y()-radius, radius*2,radius*2);
    if(drawArrow){
        double doubleAngle = (double)angle/2880*M_PI;
        QPointF endPt(windowWidth/2+arrowLength*cos(doubleAngle),windowHeight/2+arrowLength*sin(doubleAngle));
        painter->drawLine(*this->pos,endPt);
        painter->drawLine(endPt,QPointF(endPt.x()+10*cos(doubleAngle+3*M_PI/4),endPt.y()+10*sin(doubleAngle+3*M_PI/4)));
        painter->drawLine(endPt,QPointF(endPt.x()+10*cos(doubleAngle-3*M_PI/4),endPt.y()+10*sin(doubleAngle-3*M_PI/4)));
    }
}

void Ball::ghostUpdate()
{
    if(goingBrighter){
        opacity+=0.02;
    }else{
        opacity-=0.02;
    }
    if(opacity>=1.0){
        goingBrighter = false;
    }else if(opacity <= -0.10){
        goingBrighter = true;
    }
}

void Ball::initSpin()
{
    opacity = 0;
    drawArrow = true;
    arrowLength = 0;
    radius = ballInitRadius+50;
    setSpeed(0);
    angle = randomInBound(0,5760);
    for(int i = 0; i < 10; i++){
        opacity+=0.1;
        radius-=5;
        arrowLength+=7;
        QThread::msleep(refreshInterval);
    }
    int framesRotating = randomInBound(50,150);
    for(int i = 0; i < framesRotating; i++){
        angle+=96;
        QThread::msleep(refreshInterval);
    }
    setSpeed(ballInitSpeed);
    QThread::msleep((100/speed-3)*refreshInterval);
    drawArrow = false;
}

void Ball::bounce(Player* p, int pdiff, int angleWithCenter)
{
    angle = angleWithCenter+2880;
    normalize(angle);
    angle-=(((double)pdiff)/p->size*720);
    parent->mostRecent = p->playerNum;
    bouncing = true;
    collisionSound->play();
    QtConcurrent::run(this,&Ball::setBouncingToFalse);
}

void Ball::setBouncingToFalse()
{
    QThread::msleep(200);
    bouncing = false; //yes, this function serves a purpose.
}

QRectF *Ball::rect()
{
    return rekt;
}

void Ball::updateRect()
{
    rekt->setLeft(this->x()-radius);
    rekt->setTop(this->y()-radius);
    rekt->setWidth(radius*2);
    rekt->setHeight(radius*2);
}

void Ball::updatePos()
{
    pos->setX(pos->x()+speed*cos(angle*M_PI/2880));
    pos->setY(pos->y()+speed*sin(angle*M_PI/2880));
    updateRect();
    checkCollision();
}

void Ball::sizeUp()
{
    for(int i = 0; i < 5; i++){
        radius+=2;
        QThread::msleep(refreshInterval);
    }
}

void Ball::sizeDown()
{
    for(int i = 0; i < 5; i++){
        radius-=2;
        QThread::msleep(refreshInterval);
    }
}

void Ball::setPen(QPen pen)
{
    this->pen = pen;
}

void Ball::setBrush(QBrush brush)
{
    this->brush = brush;
}
