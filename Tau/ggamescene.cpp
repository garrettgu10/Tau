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
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>

GGameScene::GGameScene(Arena* box, Settings* settingsmgr)
{
    this->settingsmgr=settingsmgr;
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

    sizeUp = new QSoundEffect();
    //sizeUp->setSource(QUrl::fromLocalFile(":/sound/sizeUp.wav"));
    sizeDown = new QSoundEffect();
    //sizeDown->setSource(QUrl::fromLocalFile(":/sound/sizeDown.wav"));
}

void GGameScene::drawBoard()
{
    box->setPen(*arenaPen);
    box->setPermRadius(arenaRadius);
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
    if(scores->getScore(0)>=settingsmgr->getWinningScore()){
        win(0);
    }else if(scores->getScore(1)>=settingsmgr->getWinningScore()){
        win(1);
    }else{
        QTimer::singleShot(350,Qt::PreciseTimer,ball,SLOT(setup()));
    }
}

void GGameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(this->winner != -1 && distance(event->scenePos(),QPointF(windowWidth/2,windowHeight/2)) < arenaRadius && !endingTrigger){
        endingTrigger = true;
        endingTriggered();
    }
}

void GGameScene::exitSequence()
{
    for(int i = 0; i < 20; i++){
        p[0]->opacity-=0.05;
        p[1]->opacity-=0.05;
        winnerText->setOpacity(winnerText->getOpacity()-0.05);
        scores->setOpacity(scores->getOpacity()-0.05);
        p[0]->update();
        p[1]->update();
        QThread::msleep(defaultRefreshInterval);
    }

    while(box->radius>mainMenuArenaRadius){
        box->radius+=(mainMenuArenaRadius-box->radius)/4-3;
        box->setPermRadius(box->radius-box->pulseDist);
        QThread::msleep(defaultRefreshInterval);
    }
    QTimer::singleShot(0,Qt::CoarseTimer,addPowerUps,SLOT(stop()));

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
