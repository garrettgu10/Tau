#include "gmainmenuscene.h"
#include <QtConcurrent>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

GMainMenuScene::GMainMenuScene(Arena* box,Settings* settingsmgr)
{
    this->adjustRules(settingsmgr->getWinningScore());
    this->box = box;
    this->box->setPermRadius(mainMenuArenaRadius);
    this->box->setPen(*arenaPen);
    this->box->setRadius(mainMenuArenaRadius);
    this->addItem(this->box);
    this->addItem(this->box->bkg);
    this->box->pulseDist = 5;
    pb = new playButton(playButtonSize);
    pb->setBrush(brush);
    pb->setPen(arenaPen);
    this->addItem(pb);

    this->addItem(title);
    this->addItem(description);
    this->addItem(rules);
    creditsButton->setOpacity(0.7);
    this->addItem(creditsButton);
    QtConcurrent::run(this,&GMainMenuScene::entrySequence);
}

void GMainMenuScene::exitSequence()
{
    pb->pulsing = false;
    box->pulsing = false;
    while(box->permRadius<arenaRadius){
        title->setOpacity(title->getOpacity()-0.1);
        description->setOpacity(description->getOpacity()-0.1);
        rules->setOpacity(rules->getOpacity()-0.1);
        creditsButton->setOpacity(creditsButton->getOpacity()-0.1);
        pb->setSize(pb->getSize()-7);
        box->setPermRadius(box->permRadius+(arenaRadius-box->permRadius)/4+3);

        QThread::msleep(defaultRefreshInterval);
    }
    box->pulsing = true;
    box->radius = arenaRadius;
    box->setPermRadius(box->radius);
    doneExiting();
}

void GMainMenuScene::entrySequence()
{
    pb->setSize(0);
    title->setOpacity(0);
    description->setOpacity(0);
    rules->setOpacity(0);
    creditsButton->setOpacity(-0.3);
    pb->pulsing = false;
    for(int i = 0; i < 50; i++){
        if(pb->getSize() < playButtonSize){
            pb->setSize(pb->getSize()+2);
        }else if(!pb->pulsing){
            pb->pulsing = true;
            //pb->setSize(playButtonSize);
            QObject::connect(box,SIGNAL(pulsed()),pb,SLOT(pulse()));
        }
        title->setOpacity(title->getOpacity()+0.02);
        description->setOpacity(description->getOpacity()+0.02);
        rules->setOpacity(rules->getOpacity()+0.02);
        creditsButton->setOpacity(creditsButton->getOpacity()+0.02);
        this->update();
        QThread::msleep(defaultRefreshInterval);
    }
}

void GMainMenuScene::adjustRules(int wins)
{
    rules->setText(QString("First to ")+QString::number(wins)+QString(" wins"));
    rulesChanged(wins);
}

void GMainMenuScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    double distFromCenter = sqrt(pow(event->scenePos().x()-windowWidth/2,2)+pow(event->scenePos().y()-windowHeight/2,2));
    if(distFromCenter < mainMenuArenaRadius){
        playButtonPressed();
    }else if(this->creditsButton->containsPt(event->scenePos().toPoint())){
        creditsButtonPressed();
    }
}

void GMainMenuScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(this->creditsButton->containsPt(event->scenePos().toPoint())){
        this->creditsButton->setOpacity(1);
    }else{
        this->creditsButton->setOpacity(0.7);
    }
}

void GMainMenuScene::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if(key > Qt::Key_0 && key <= Qt::Key_9){
        this->adjustRules(key-Qt::Key_0);
    }else if(event->key() == Qt::Key_Space){
        playButtonPressed();
    }
}

void GMainMenuScene::refresh()
{
    if(box->radius > box->permRadius && box->pulsing)
        box->setRadius(box->radius-1);
    if(pb->getSize() > pb->permSize)
        pb->setSize(pb->getSize()-1);

    pb->incrementAngle();
    this->update();
}
