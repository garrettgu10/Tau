#include "ggamescene.h"
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <math.h>
#include <constants.h>
#include <player.h>
#include <QTimer>
#include <ball.h>
#include <arena.h>
#include <QtConcurrent>
#include <QGraphicsView>

GGameScene::GGameScene()
{
    p[0] = new Player(2880,playerInitSize,0);
    p[1] = new Player(0,playerInitSize,1);
    mostRecent = 0;
    b = new Ball(this);
    powerUps = new QList<powerup*>();
    QTimer* addPowerUps = new QTimer();
    QObject::connect(addPowerUps,SIGNAL(timeout()),this,SLOT(addPowerUp()));
    addPowerUps->setTimerType(Qt::PreciseTimer);
    addPowerUps->start(powerUpInterval);
    refresher = new QTimer();
    QObject::connect(refresher,SIGNAL(timeout()), this,SLOT(refresh()));
    refresher->setTimerType(Qt::PreciseTimer);

    sizeUp = new QSoundEffect();
    sizeUp->setSource(QUrl::fromLocalFile(":/sound/sizeUp.wav"));
    sizeDown = new QSoundEffect();
    sizeDown->setSource(QUrl::fromLocalFile(":/sound/sizeDown.wav"));
}

void GGameScene::drawGradBackground()
{
    QGraphicsRectItem* rect = new QGraphicsRectItem();
    QRadialGradient grad(this->width()/2,this->height()/2, this->height()/2);
    grad.setColorAt(0,QColor::fromRgb(100,100,100,255));
    grad.setColorAt(1,QColor::fromRgb(0,0,0,255));
    QBrush brush(grad);
    QPen clear(QColor::fromRgb(255,255,255,0));
    rect->setBrush(brush);
    rect->setPen(clear);
    rect->setRect(0,0,this->width(),this->height());
    this->addItem(rect);
}

void GGameScene::drawBoard()
{
    Arena* box = new Arena();
    box->setPen(*arenaPen);
    box->setRect(windowWidth/2-arenaRadius,windowHeight/2-arenaRadius,arenaRadius*2,arenaRadius*2);
    this->addItem(box);
    //draw players

    QPen player1Pen(*arenaPen);
    player1Pen.setColor(QColor::fromRgb(0,0,255));
    player1Pen.setWidth(playerWidth);
    player1Pen.setCapStyle(Qt::RoundCap);
    p[0]->setPen(player1Pen);
    this->addItem(p[0]);
    QPen player2Pen(player1Pen);
    player2Pen.setColor(QColor::fromRgb(255,0,0));
    p[1]->setPen(player2Pen);
    this->addItem(p[1]);
    b->setPen(*arenaPen);
    b->setBrush(*brush);
    this->addItem(b);
    refresher->start(refreshInterval);
    addPowerUp();
}

void GGameScene::addPowerUp()
{
    powerup* newPowerup = new powerup(powerUps->size(),this);
    newPowerup->setPen(*arenaPen);
    newPowerup->setBrush(*brush);
    powerUps->append(newPowerup);
    this->addItem(newPowerup);
}

void GGameScene::collectedPowerup(powerup *p)
{
    if(!p->enabled){
        p->enable();
        this->removeItem(p);
    }
}

void GGameScene::gameOver()
{
    b->disabled = true;
    for(powerup* p: *powerUps){
        p->disable();
        powerUps->removeOne(p);
        if(p->scene() == this){
            this->removeItem(p);
        }
    }
    QtConcurrent::run(b,&Ball::explode);
    QTimer::singleShot(350,Qt::PreciseTimer,b,SLOT(setup()));
}

void GGameScene::refresh()
{
    b->updatePos();
    this->update();
}
