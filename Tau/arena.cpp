#include "arena.h"
#include <QPainter>
#include <QGraphicsEllipseItem>

Arena::Arena()
{
    radius = permRadius;
    grad->setColorAt(0,QColor(0,0,0,0));
    grad->setColorAt(1,QColor::fromRgb(0,0,0,255));
}

void Arena::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(QBrush(*grad));
    painter->setPen(*clear);
    painter->drawRect(0,0,windowWidth,windowHeight);
    painter->setPen(*redPen);
    painter->setBrush(this->brush());
    painter->drawArc(rect(), -1440, 2880);
    painter->setPen(*bluePen);
    painter->drawArc(rect(),1440,2880);
}

void Arena::setPen(const QPen &pen)
{
    bluePen = new QPen(pen);
    bluePen->setColor(QColor::fromRgb(165,165,255));
    redPen = new QPen(pen);
    redPen->setColor(QColor::fromRgb(255,165,165));
}

void Arena::setRadius(int rad)
{
    this->radius = rad;
    this->setRect(windowWidth/2-rad,windowHeight/2-rad,rad*2,rad*2);
}

void Arena::startPulse(int bpm)
{
    updateBg = new QTimer();
    updateBg->setTimerType(Qt::PreciseTimer);
    pulse();
    QObject::connect(updateBg,SIGNAL(timeout()),this,SLOT(pulse()));
    updateBg->start(60000/bpm);
}

void Arena::setPermRadius(int prad)
{
    this->permRadius = prad;
    grad->setRadius(permRadius/0.9);
}

void Arena::pulse()
{
    pulsed();
    grad->setColorAt(0,QColor::fromRgb(randomInBound(50,150),randomInBound(50,150),randomInBound(50,150),255));

    setRadius(permRadius+pulseDist);
}

void Arena::changeBPM(int i)
{
    updateBg->stop();
    if(BPM[i]!=0){
        updateBg->start(60000/BPM[i]);
    }else{
        this->grad->setColorAt(0,QColor::fromRgb(150,150,150,255));
    }
}
