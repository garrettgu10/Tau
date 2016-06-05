#include "ball.h"
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

    clearPen = QPen(QColor::fromRgb(0,0,0,0));

    warper = new QTimer();
    QObject::connect(warper,SIGNAL(timeout()),this,SLOT(warpToggleSpeeds()));
    wobbler = new QTimer();
    QObject::connect(wobbler,SIGNAL(timeout()),this,SLOT(wobble()));
    ghoster = new QTimer();
    QObject::connect(ghoster, SIGNAL(timeout()),this,SLOT(ghostUpdate()));
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
    normalize(angle);
    this->angle = angle;
    this->permAngle = angle;
    if(speed!=0)
        updateImpactAngle();
}

void Ball::explode()
{
    speed = 0;
    opacity = 1.0;
    for(int i = 0; i < 10; i++){
        opacity-=0.1;
        radius+=5;
        updateRect();
        QThread::msleep(defaultRefreshInterval);
    }
}

void Ball::startGhost()
{
    if(!ghoster->isActive()){
        opacity = 1.0;
        goingBrighter = false;
        ghoster->start(defaultRefreshInterval);
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

bool Ball::setSpeed(double newSpeed)
{
    if(speed==0 && newSpeed!=0){
        updateImpactAngle();
    }
    if(newSpeed>=0){
        speed = newSpeed;
        return true;
    }
    return false;
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

    this->rekt->setX(pos->x()-100);
    this->rekt->setY(pos->y()-100);
    this->rekt->setWidth(200);
    this->rekt->setHeight(200);

    QtConcurrent::run(this,&Ball::initSpin);
}

void Ball::startWobble(){
    wobbler->start(100);
}

void Ball::wobble()
{
    angle = permAngle+randomInBound(-720,720);
    updateImpactAngle();
}

void Ball::warpToggleSpeeds()
{
    if(warpSpedUp){
        setSpeed(speed-2.5);
        warpSpedUp = false;
    }else{
        setSpeed(speed+2.5);
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
            if(p->boundingRect().intersects(this->boundingRect()) && distance(this->pos,p->pos()) < this->radius+p->rad()){
                parent->collectedPowerup(p);
            }
        }
    }
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*unused*/, QWidget * /*unused*/)
{
    painter->setClipRect(boundingRect());
    painter->setBrush(this->brush);
    painter->setOpacity(opacity);
    painter->setPen(clearPen);
    painter->drawEllipse(pos->x()-radius,pos->y()-radius, radius*2,radius*2);
    painter->setPen(this->pen);
    if(drawArrow){
        double doubleAngle = (double)angle/2880*M_PI;
        QPointF endPt(windowWidth/2+arrowLength*cos(doubleAngle),windowHeight/2+arrowLength*sin(doubleAngle));
        painter->drawLine(*this->pos,endPt);
        painter->drawLine(endPt,QPointF(endPt.x()+10*cos(doubleAngle+3*M_PI/4),endPt.y()+10*sin(doubleAngle+3*M_PI/4)));
        painter->drawLine(endPt,QPointF(endPt.x()+10*cos(doubleAngle-3*M_PI/4),endPt.y()+10*sin(doubleAngle-3*M_PI/4)));
    }
}

void Ball::updateImpactAngle()
{
    updateImpactPoint();
    impactAngle = arcTan(impactPoint.x()-windowWidth/2,impactPoint.y()-windowHeight/2);
}

void Ball::updateImpactPoint()
{
    double slope = tan((double)this->permAngle/2880*M_PI);
    QPointF center(windowWidth/2,windowHeight/2);
    double yint = (this->pos->y()-center.y())-(this->pos->x()-center.x())*slope;

    //calculate two intersections of line with circle
    double x1 = (-2*slope*yint+sqrt(pow(2*slope*yint,2)-4*(1+slope*slope)*(yint*yint-pow(arenaRadius-this->radius,2))))/2/(1+slope*slope)+center.x();
    // works on paper
    double y1 = this->pos->y()-(this->pos->x()-x1)*slope;

    double x2 = (-2*slope*yint-sqrt(pow(2*slope*yint,2)-4*(1+slope*slope)*(yint*yint-pow(arenaRadius-this->radius,2))))/2/(1+slope*slope)+center.x();
    double y2 = this->pos->y()-(this->pos->x()-x2)*slope;

    if(permAngle >1440 && permAngle < 4320){
        // ball is going left
        if(x1 < x2){
            this->impactPoint.setX(x1);
            this->impactPoint.setY(y1);
        }else{
            this->impactPoint.setX(x2);
            this->impactPoint.setY(y2);
        }
    }else{
        if(x1 > x2){
            this->impactPoint.setX(x1);
            this->impactPoint.setY(y1);
        }else{
            this->impactPoint.setX(x2);
            this->impactPoint.setY(y2);
        }
    }
}

int Ball::getImpactAngle() const
{
    return impactAngle;
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
    }else if(opacity <= -0.15){
        goingBrighter = true;
    }
}

int Ball::getAngle() const
{
    return angle;
}

void Ball::initSpin()
{
    seedRandomFunction();
    opacity = 0;
    drawArrow = true;
    arrowLength = 0;
    radius = ballInitRadius+50;
    setSpeed(0);
    this->setAngle(randomInBound(0,5760));
    for(int i = 0; i < 10; i++){
        opacity+=0.1;
        radius-=5;
        arrowLength+=7;
        QThread::msleep(defaultRefreshInterval);
    }
    int framesRotating = randomInBound(50,150);
    for(int i = 0; i < framesRotating; i++){
        setAngle(angle+96);
        QThread::msleep(defaultRefreshInterval);
    }
    setSpeed(ballInitSpeed);
    QThread::msleep((100/speed-3)*defaultRefreshInterval);
    drawArrow = false;
}

void Ball::bounce(Player* p, int pdiff, int angleWithCenter)
{
    angle = angleWithCenter+2880;
    normalize(angle);
    setAngle(angle-(((double)pdiff)/p->size*720));
    parent->mostRecent = p->playerNum;
    bouncing = true;
    QtConcurrent::run(this,&Ball::setBouncingToFalse);
}

void Ball::setBouncingToFalse()
{
    QThread::msleep(200);
    bouncing = false;
}

QRectF *Ball::rect()
{
    return rekt;
}

void Ball::updateRect()
{
    rekt->setLeft(this->pos->x()-radius);
    rekt->setTop(this->pos->y()-radius);
    rekt->setWidth(radius*2);
    rekt->setHeight(radius*2);
}

void Ball::updatePos()
{
    pos->setX(pos->x()+speed*cos(angle*M_PI/2880));
    pos->setY(pos->y()+speed*sin(angle*M_PI/2880));
    if(speed!=0)
        updateRect();
    checkCollision();
}

void Ball::sizeUp()
{
    for(int i = 0; i < 5; i++){
        radius+=2;
        QThread::msleep(defaultRefreshInterval);
    }
    updateRect();
}

void Ball::sizeDown()
{
    for(int i = 0; i < 5; i++){
        radius-=2;
        QThread::msleep(defaultRefreshInterval);
    }
    updateRect();
}

void Ball::setPen(QPen pen)
{
    this->pen = pen;
}

void Ball::setBrush(QBrush brush)
{
    this->brush = brush;
}
