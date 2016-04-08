#include "ggraphicsscene.h"
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <math.h>
#include <player.h>

GGraphicsScene::GGraphicsScene(){
    p1 = new Player(0,180);
    p2 = new Player(1440,180);
}

void GGraphicsScene::drawGradBackground(){
    QGraphicsRectItem* rect = new QGraphicsRectItem();
    QRadialGradient grad(this->width()/2,this->height()/2, this->width()/2);
    grad.setColorAt(0,QColor::fromRgb(100,100,100,255));
    grad.setColorAt(1,QColor::fromRgb(0,0,0,255));
    QBrush brush(grad);
    QPen clear(QColor::fromRgb(255,255,255,0));
    rect->setBrush(brush);
    rect->setPen(clear);
    rect->setRect(0,0,this->width(),this->height());
    this->addItem(rect);
}



void GGraphicsScene::drawBoard()
{
    QGraphicsEllipseItem* box = new QGraphicsEllipseItem();
    arenaRadius = this->height()/2*.8;
    int playerRadius = arenaRadius-12;
    QBrush brush(QColor::fromRgb(255,0,255));
    QPen arenaPen(brush,5,Qt::SolidLine,Qt::RoundCap);
    box->setPen(arenaPen);
    box->setRect(this->width()/2-arenaRadius,this->height()/2-arenaRadius,arenaRadius*2,arenaRadius*2);
    this->addItem(box);
    //draw players

    QPen player1Pen(arenaPen);
    player1Pen.setColor(QColor::fromRgb(0,0,255));
    player1Pen.setWidth(15);
    p1->setPen(player1Pen);
    p1->setStartAngle(p1->pos-p1->size + 2*M_PI);
    p1->setSpanAngle(p1->size*2);
    p1->setRect(this->width()/2-playerRadius,this->height()/2-playerRadius,playerRadius*2,playerRadius*2);
    this->addItem(p1);
}
