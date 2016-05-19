#include "ggraphicsview.h"
#include <QDebug>
#include <QMouseEvent>
#include <QTime>
#include <QtConcurrent>
#include <QThread>
#include <arena.h>
#include <QGraphicsRectItem>
#include <titletext.h>
#include <QDesktopServices>
#include <QUrl>

GGraphicsView::GGraphicsView(Settings* settingsmgr)
{
    movement[0] = NONE;
    movement[1] = NONE;
    this->settingsmgr = settingsmgr;
    winningScore = settingsmgr->getWinningScore();

    box = new Arena();
    MScene = new GMainMenuScene(box,settingsmgr);
    MScene->setSceneRect(0,0,windowWidth,windowHeight);
    this->setScene(MScene);

    music = new QMediaPlayer();
    playlist = new QMediaPlaylist();
    for(int i = 0; i < numSongs;i++){
        playlist->addMedia(QUrl("qrc:/sound/"+songs[i]+".mp3"));
    }
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    music->setPlaylist(playlist);

    music->setVolume(100);
    music->play();
    playlist->setCurrentIndex(randomInBound(0,numSongs-1));

    box->startPulse(BPM[playlist->currentIndex()]);
    QObject::connect(playlist,SIGNAL(currentIndexChanged(int)),box,SLOT(changeBPM(int)));

    this->setMouseTracking(true);

    refresher = new QTimer();
    refresher->setTimerType(Qt::PreciseTimer);
    QObject::connect(refresher,SIGNAL(timeout()),this,SLOT(refresh()));
    refresher->start(refreshInterval);

    //startGame();
}

void GGraphicsView::setGScene(GGameScene *scene)
{
    this->setScene(scene);
    this->GScene = scene;
}

void GGraphicsView::startGame()
{
    if(!startedGame){
        GScene = new GGameScene(box,settingsmgr);
        setGScene(GScene);
        QTimer::singleShot(1000,Qt::CoarseTimer,MScene,SLOT(deleteLater()));
        QtConcurrent::run(GScene->p[0],&Player::fadeIn);
        QtConcurrent::run(GScene->p[1],&Player::fadeIn);
        box->pulseDist = 10;
        box->setPermRadius(arenaRadius);
        GScene->ball->setup();
        GScene->setSceneRect(0,0,windowWidth,windowHeight);
        GScene->drawBoard();
        startedGame = true;
    }
}

void GGraphicsView::startMainMenu()
{
    if(startedGame){
        MScene = new GMainMenuScene(box,settingsmgr);
        QTimer::singleShot(1000,Qt::CoarseTimer,GScene,SLOT(deleteLater()));
        setScene(MScene);
        box->pulseDist = 5;
        box->setPermRadius(mainMenuArenaRadius);
        startedGame = false;
    }
}

void GGraphicsView::refresh()
{
    if(startedGame){
        GScene->refresh();
        for(int i = 0; i <=1; i++){
            if(movement[i]!=NONE){
                if(movement[i]==CLOCKWISE){
                    GScene->p[i]->moveClockwise();
                }else{
                    GScene->p[i]->moveCClockwise();
                }
            }
        }
    }else{
        MScene->refresh();
    }
}

void GGraphicsView::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat()){
        return;
    }
    int key = event->key();
    if(startedGame && GScene->winner!=-1 && key==Qt::Key_Space){
        startEndSequence();
    }

    if(!startedGame && key > Qt::Key_0 && key <= Qt::Key_9){
        MScene->adjustRules(key-Qt::Key_0);
        winningScore = key-Qt::Key_0;
        settingsmgr->setWinningScore(winningScore);
        settingsmgr->save();
    }
    int affectedPlayer = -1;
    bool cw = false; //clockwise

    switch(key){
    case Qt::Key_Return: playlist->setCurrentIndex(playlist->currentIndex()==playlist->mediaCount()-1?0:playlist->currentIndex()+1); return;
    case Qt::Key_D:
    case Qt::Key_W: affectedPlayer = 0; cw = true;  break;
    case Qt::Key_A:
    case Qt::Key_S: affectedPlayer = 0; cw = false; break;
    case Qt::Key_Left:
    case Qt::Key_Up: affectedPlayer= 1; cw = false; break;
    case Qt::Key_Right:
    case Qt::Key_Down: affectedPlayer=1;cw = true;  break;
    }

    if(!startedGame)
        return;

    if(affectedPlayer!=-1){
        movement[affectedPlayer] = (paddleMove)(ANTICLOCKWISE+cw);
    }
}

void GGraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    if(!startedGame)
        return;
    if(!event->isAutoRepeat()){
        int key = event->key();
        int affectedPlayer = -1;
        bool cw = false;
        switch(key){
        case Qt::Key_D:
        case Qt::Key_W: affectedPlayer = 0; cw = true; break;
        case Qt::Key_A:
        case Qt::Key_S: affectedPlayer = 0; cw = false; break;
        case Qt::Key_Left:
        case Qt::Key_Up: affectedPlayer= 1; cw = false; break;
        case Qt::Key_Right:
        case Qt::Key_Down: affectedPlayer=1;cw = true; break;
        }
        if(movement[affectedPlayer]-ANTICLOCKWISE == cw){
            movement[affectedPlayer] = NONE;
        }
    }
}

void GGraphicsView::openCredits()
{
    QDesktopServices::openUrl(QUrl("https://github.com/garrettgu10/Tau/blob/master/Tau/LICENSE.md", QUrl::TolerantMode));
}

void GGraphicsView::startEndSequence()
{
    QtConcurrent::run(GScene,&GGameScene::exitSequence);
    QObject::connect(GScene,SIGNAL(doneExiting()),this,SLOT(startMainMenu()));
}

void GGraphicsView::startBeginSequence()
{
    QtConcurrent::run(MScene,&GMainMenuScene::exitSequence);
    QObject::connect(MScene,SIGNAL(doneExiting()),this,SLOT(startGame()));
}

void GGraphicsView::closeEvent(QCloseEvent * /*unused*/)
{
    this->music->stop();
    if(startedGame){
        GScene->ongoing = false;
    }
}

void GGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(startedGame)
        return;
    double distFromCenter = sqrt(pow(event->x()-windowWidth/2,2)+pow(event->y()-windowHeight/2,2));
    if(distFromCenter < mainMenuArenaRadius){
        startBeginSequence();
    }

    if(!startedGame && MScene->creditsButton->containsPt(event->pos())){
        openCredits();
    }
}

void GGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if(startedGame)
        return;
    if(MScene->creditsButton->containsPt(event->pos())){
        MScene->creditsButton->opacity = 1;
    }else{
        MScene->creditsButton->opacity = 0.7;
    }
}
