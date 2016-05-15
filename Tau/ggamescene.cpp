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
#include <titletext.h>
#include <QMediaMetaData>

GGameScene::GGameScene(Arena* box, Settings* settingsmgr)
{
    this->winningScore = settingsmgr->getWinningScore();
    for(int i = 0; i < (int)powerUpType::NUM_POWERUPTYPES; i++){
        overlappingPups[i] = 0;
    }
    this->box = box;
    scores = new ScoreDisplay();
    p[0] = new Player(2880,playerInitSize,0);
    p[1] = new Player(0,playerInitSize,1);
    mostRecent = 0;
    ball = new Ball(this);
    powerUps = new QList<powerup*>();
    addPowerUps = new QTimer();
    QObject::connect(addPowerUps,SIGNAL(timeout()),this,SLOT(addPowerUp()));
    addPowerUps->setTimerType(Qt::PreciseTimer);
    refresher = new QTimer();
    QObject::connect(refresher,SIGNAL(timeout()), this,SLOT(refresh()));
    refresher->setTimerType(Qt::PreciseTimer);

    sizeUp = new QSoundEffect();
    //sizeUp->setSource(QUrl::fromLocalFile(":/sound/sizeUp.wav"));
    sizeDown = new QSoundEffect();
    //sizeDown->setSource(QUrl::fromLocalFile(":/sound/sizeDown.wav"));
}

void GGameScene::drawBoard()
{
    box->setPen(*arenaPen);
    box->setRect(windowWidth/2-arenaRadius,windowHeight/2-arenaRadius,arenaRadius*2,arenaRadius*2);
    this->addItem(box);
    this->addItem(box->bkg);
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

    ball->setPen(*arenaPen);
    ball->setBrush(*brush);
    this->addItem(ball);

    scores->setPen(*arenaPen);
    scores->setBrush(*brush);
    this->addItem(scores);
    refresher->start(refreshInterval);
    addPowerUps->start(powerUpInterval);
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

void GGameScene::win(int winner)
{
    this->winner = winner;
    winnerText=new titleText("Georgia",new QPointF(windowWidth/2,windowHeight/2+10),20,(winner==0? QString("Blue"):QString("Red"))+QString(" wins. "
                                                                                                                                        "Press space to continue."));
    this->addItem(winnerText);
    addPowerUps->stop();
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
    ball->disabled = true;
    for(powerup* p: *powerUps){
        p->disable();
        powerUps->removeOne(p);
        if(p->scene() == this){
            this->removeItem(p);
        }
    }
    if(ball->pos->x() > windowWidth/2){
        scores->score(0);
    }else{
        scores->score(1);
    }
    QtConcurrent::run(ball,&Ball::explode);
    if(scores->getScore(0)>=winningScore){
        win(0);
    }else if(scores->getScore(1)>=winningScore){
        win(1);
    }else{
        QTimer::singleShot(350,Qt::PreciseTimer,ball,SLOT(setup()));
    }
}

void GGameScene::exitSequence()
{
    for(int i = 0; i < 20; i++){
        p[0]->opacity-=0.05;
        p[1]->opacity-=0.05;
        winnerText->opacity-=0.05;
        scores->opacity-=0.05;
        QThread::msleep(refreshInterval);
    }

    while(box->radius>mainMenuArenaRadius){
        box->radius-=30;
        box->radius+=(mainMenuArenaRadius-box->radius)/3-3;
        box->setPermRadius(box->radius-box->pulseDist);
        QThread::msleep(refreshInterval);
    }

    doneExiting();
}

void GGameScene::refresh()
{
    ball->updatePos();
    this->update();
    if(box->radius>box->permRadius){
        box->setRadius(box->radius-1);
    }
}
