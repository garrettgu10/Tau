#include "gmainmenuscene.h"
#include <QtConcurrent>

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
    creditsButton->opacity=0.7;
    this->addItem(creditsButton);
    QtConcurrent::run(this,&GMainMenuScene::entrySequence);
}

void GMainMenuScene::exitSequence()
{
    while(box->radius<arenaRadius){
        title->opacity-=0.1;
        description->opacity-=0.1;
        rules->opacity-=0.1;
        creditsButton->opacity-=0.1;
        pb->setSize(pb->getSize()-7);
        box->radius+=(arenaRadius-box->radius)/3+3;
        box->setPermRadius(box->radius-box->pulseDist);
        QThread::msleep(refreshInterval);
    }
    doneExiting();
}

void GMainMenuScene::entrySequence()
{
    pb->setSize(0);
    title->opacity = 0;
    description->opacity = 0;
    rules->opacity = 0;
    creditsButton->opacity=-0.3;
    for(int i = 0; i < 50; i++){
        if(pb->getSize() < playButtonSize)
            pb->setSize(pb->getSize()+2);
        title->opacity+=0.02;
        description->opacity+=0.02;
        rules->opacity+=0.02;
        creditsButton->opacity+=0.02;
        QThread::msleep(refreshInterval);
    }
    QObject::connect(box,SIGNAL(pulsed()),pb,SLOT(pulse()));
    pb->setSize(playButtonSize);
}

void GMainMenuScene::adjustRules(int wins)
{
    rules->setText(QString("First to ")+QString::number(wins)+QString(" wins"));
}

void GMainMenuScene::refresh()
{
    if(box->radius > box->permRadius)
        box->setRadius(box->radius-1);
    pb->incrementAngle();
    if(pb->getSize() > pb->permSize)
        pb->setSize(pb->getSize()-1);
    this->update();
}
