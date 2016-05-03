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
#include <QMediaMetaData>

GGameScene::GGameScene(Arena* box)
{
    for(int i = 0; i < (int)powerUpType::NUM_POWERUPTYPES; i++){
        overlappingPups[i] = 0;
    }
    this->box = box;
    scores = new ScoreDisplay();
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
    for(int i = 0; i < numSongs;i++){
        playlist->addMedia(QUrl("qrc:/sound/"+songs[i]+".mp3"));
    }
    playlist->setPlaybackMode(QMediaPlaylist::Random);

    music->setPlaylist(playlist);

    music->setVolume(100);
    music->play();
    playlist->setCurrentIndex(randomInBound(0,numSongs-1));
    qDebug() << playlist->currentIndex();

    updateBg = new QTimer();
    updateBg->setTimerType(Qt::PreciseTimer);
    box->pulse();
    QObject::connect(updateBg,SIGNAL(timeout()),box,SLOT(pulse()));
    updateBg->start(60000/BPM[playlist->currentIndex()]);
    QObject::connect(playlist,SIGNAL(currentIndexChanged(int)),this,SLOT(changeBPM(int)));

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
    scores->setPen(*arenaPen);
    scores->setBrush(*brush);
    this->addItem(scores);
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

void GGameScene::changeBPM(int i)
{
    updateBg->stop();
    if(BPM[i]!=0){
        updateBg->start(60000/BPM[i]);
    }else{
        box->grad->setColorAt(0,QColor::fromRgb(150,150,150,255));
    }
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
    if(b->pos->x() > windowWidth/2){
        scores->score(0);
    }else{
        scores->score(1);
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
