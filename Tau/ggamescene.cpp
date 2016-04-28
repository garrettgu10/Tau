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
#include <helper.h>

GGameScene::GGameScene()
{
    box = new Arena();
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

    music = new QMediaPlayer();
    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sound/music.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    music->setPlaylist(playlist);

    music->setVolume(100);
    music->play();

    initGradBackground();

    QTimer* updateBg = new QTimer();
    updateBg->setTimerType(Qt::PreciseTimer);
    QObject::connect(updateBg,SIGNAL(timeout()),this,SLOT(updateGradBackground()));
    updateBg->start(469);

    sizeUp = new QSoundEffect();
    //sizeUp->setSource(QUrl::fromLocalFile(":/sound/sizeUp.wav"));
    sizeDown = new QSoundEffect();
    //sizeDown->setSource(QUrl::fromLocalFile(":/sound/sizeDown.wav"));
}

void GGameScene::updateGradBackground()
{
    grad->setColorAt(0,QColor::fromRgb(randomInBound(50,150),randomInBound(50,150),randomInBound(50,150),255));

    QBrush brush(*grad);
    QPen clear(QColor::fromRgb(255,255,255,0));
    BgRect->setBrush(brush);
    BgRect->setPen(clear);
    BgRect->setRect(0,0,this->width(),this->height());
    box->setRadius(arenaRadius+10);
}

void GGameScene::drawBoard()
{
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

void GGameScene::initGradBackground()
{
    grad = new QRadialGradient(windowWidth/2,windowHeight/2, windowHeight/2);
    grad->setColorAt(1,QColor::fromRgb(0,0,0,255));
    updateGradBackground();
    this->addItem(BgRect);
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
    if(box->radius>arenaRadius){
        box->setRadius(box->radius-1);
    }
}
