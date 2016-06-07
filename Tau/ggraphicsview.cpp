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
#include <skynet.h>

GGraphicsView::GGraphicsView(Settings* settingsmgr)
{
    movement[0] = NONE;
    movement[1] = NONE;

    this->settingsmgr = settingsmgr;

    box = new Arena();
    MScene = new GMainMenuScene(box,settingsmgr);
    MScene->setSceneRect(0,0,windowWidth,windowHeight);
    this->setScene(MScene);
    QObject::connect(MScene,SIGNAL(playButtonPressed()),this,SLOT(startBeginSequence()));
    QObject::connect(MScene,SIGNAL(creditsButtonPressed()),this,SLOT(openCredits()));
    QObject::connect(MScene,SIGNAL(rulesChanged(int)),this,SLOT(changeRules(int)));
    //this->setMinimumSize(windowWidth/2,windowHeight/2);

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
    refresher->start(defaultRefreshInterval);

    this->setCacheMode(QGraphicsView::CacheBackground);
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
        movement[0] = NONE;
        movement[1] = NONE;
        GScene->setSceneRect(0,0,windowWidth,windowHeight);
        GScene->drawBoard();
        settingsmgr->incrementNumGames();

        if(settingsmgr->getAIModeEnabled()){
            skynet* ai = new skynet(GScene->ball,GScene->p[0]);
            //skynet* ai2 = new skynet(GScene->ball,GScene->p[1]);
            QObject::connect(refresher,SIGNAL(timeout()),ai,SLOT(act()));
            //QObject::connect(refresher,SIGNAL(timeout()),ai2,SLOT(act()));
        }

        startedGame = true;
    }
}

void GGraphicsView::startMainMenu()
{
    if(startedGame){
        MScene = new GMainMenuScene(box,settingsmgr);
        QObject::connect(MScene,SIGNAL(playButtonPressed()),this,SLOT(startBeginSequence()));
        QObject::connect(MScene,SIGNAL(creditsButtonPressed()),this,SLOT(openCredits()));
        QObject::connect(MScene,SIGNAL(rulesChanged(int)),this,SLOT(changeRules(int)));
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
            switch(movement[i]){
            case NONE: break;
            case CLOCKWISE: GScene->p[i]->moveClockwise(); break;
            case ANTICLOCKWISE: GScene->p[i]->moveCClockwise(); break;
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

    if(!startedGame){
        MScene->keyPressEvent(event);
    }

    int affectedPlayer = -1;
    bool cw = false; //clockwise

    if(key == Qt::Key_Return){
        playlist->setCurrentIndex(playlist->currentIndex()==playlist->mediaCount()-1?0:playlist->currentIndex()+1);
    }

    getMovementRules(key,affectedPlayer,cw);

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

        getMovementRules(key,affectedPlayer,cw);

        if(movement[affectedPlayer]-ANTICLOCKWISE == cw){
            movement[affectedPlayer] = NONE;
        }
    }
}

void GGraphicsView::resizeEvent(QResizeEvent *)
{
    this->resetTransform();
    if((double)this->width()/windowWidth > (double)this->height()/windowHeight){
        this->scale((double)this->height()/windowHeight,(double)this->height()/windowHeight);
    }else{
        this->scale((double)this->width()/windowWidth,(double)this->width()/windowWidth);
    }
}

void GGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(startedGame){
        if(event->x()>this->width()/2){
            if(event->y()>this->height()/2){
                keyPressEvent(new QKeyEvent(QEvent::KeyPress,Qt::Key_Down,Qt::KeyboardModifierMask));
            }else{
                keyPressEvent(new QKeyEvent(QEvent::KeyPress,Qt::Key_Up,Qt::KeyboardModifierMask));
            }
        }else{
            if(event->y()>this->height()/2){
                keyPressEvent(new QKeyEvent(QEvent::KeyPress,Qt::Key_S,Qt::KeyboardModifierMask));
            }else{
                keyPressEvent(new QKeyEvent(QEvent::KeyPress,Qt::Key_W,Qt::KeyboardModifierMask));
            }
        }
    }
    QGraphicsView::mousePressEvent(event);
}

void GGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if(startedGame){
        if(event->x()>this->width()/2){
            if(event->y()>this->height()/2){
                keyReleaseEvent(new QKeyEvent(QEvent::KeyPress,Qt::Key_Down,Qt::KeyboardModifierMask));
            }else{
                keyReleaseEvent(new QKeyEvent(QEvent::KeyPress,Qt::Key_Up,Qt::KeyboardModifierMask));
            }
        }else{
            if(event->y()>this->height()/2){
                keyReleaseEvent(new QKeyEvent(QEvent::KeyPress,Qt::Key_S,Qt::KeyboardModifierMask));
            }else{
                keyReleaseEvent(new QKeyEvent(QEvent::KeyPress,Qt::Key_W,Qt::KeyboardModifierMask));
            }
        }
    }
    QGraphicsView::mousePressEvent(event);
}

void GGraphicsView::getMovementRules(int key, int &affectedPlayer, bool &cw)
{
    switch(key){
    case Qt::Key_D:
    case Qt::Key_W: affectedPlayer = 0; cw = true;  break;
    case Qt::Key_A:
    case Qt::Key_S: affectedPlayer = 0; cw = false; break;
    case Qt::Key_Left:
    case Qt::Key_Up: affectedPlayer= 1; cw = false; break;
    case Qt::Key_Right:
    case Qt::Key_Down: affectedPlayer=1;cw = true;  break;
    }
}

void GGraphicsView::openCredits()
{
    QDesktopServices::openUrl(QUrl("https://github.com/garrettgu10/Tau/blob/master/Tau/LICENSE.md", QUrl::TolerantMode));
}

void GGraphicsView::changeRules(int wins)
{
    settingsmgr->setWinningScore(wins);
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
