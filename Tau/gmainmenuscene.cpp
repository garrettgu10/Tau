#include "gmainmenuscene.h"

GMainMenuScene::GMainMenuScene(Arena* box)
{
    this->box = box;
    this->box->setPermRadius(mainMenuArenaRadius);
    this->box->setPen(*arenaPen);
    this->box->setRadius(mainMenuArenaRadius);
    this->addItem(this->box);
    this->box->pulseDist = 5;
    pb = new playButton(playButtonSize);
    pb->setBrush(brush);
    pb->setPen(arenaPen);
    this->addItem(pb);
    QObject::connect(box,SIGNAL(pulsed()),pb,SLOT(pulse()));
    refresher = new QTimer();
    QObject::connect(refresher,SIGNAL(timeout()),this,SLOT(refresh()));
    refresher->start(refreshInterval);
    title = new titleText(new QPointF(windowWidth/2,windowHeight/4),200,"\u03C4");
    this->addItem(this->title);
}

void GMainMenuScene::exitSequence()
{
    box->pulseDist = 10;
    while(box->radius<arenaRadius){
        title->opacity-=0.1;
        pb->setSize(pb->getSize()-7);
        box->radius+=(arenaRadius-box->radius)/3+3;
        box->setPermRadius(box->radius-box->pulseDist);
        QThread::msleep(refreshInterval);
    }
    doneExiting();
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
