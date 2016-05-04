#include "gmainmenuscene.h"

GMainMenuScene::GMainMenuScene(Arena* box)
{
    this->box = box;
    this->box->setPermRadius(mainMenuArenaRadius);
    this->box->setPen(*arenaPen);
    this->box->setRadius(mainMenuArenaRadius);
    this->addItem(this->box);
    this->update();
    this->box->pulseDist = 5;

    refresher = new QTimer();
    QObject::connect(refresher,SIGNAL(timeout()),this,SLOT(refresh()));
    refresher->start(refreshInterval);
}

void GMainMenuScene::refresh()
{
    if(box->radius > box->permRadius)
        box->setRadius(box->radius-1);
    this->update();
}
