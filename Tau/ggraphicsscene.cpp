#include "ggraphicsscene.h"
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <math.h>
#include <constants.h>
#include <player.h>

GGraphicsScene::GGraphicsScene(){
    p1 = new Player(2880,180);
    p2 = new Player(0,180);
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

    QBrush brush(QColor::fromRgb(255,0,255));
    QPen arenaPen(brush,arenaWidth,Qt::SolidLine,Qt::RoundCap);
    box->setPen(arenaPen);
    box->setRect(windowWidth/2-arenaRadius,windowHeight/2-arenaRadius,arenaRadius*2,arenaRadius*2);
    this->addItem(box);
    //draw players

    QPen player1Pen(arenaPen);
    player1Pen.setColor(QColor::fromRgb(0,0,255));
    player1Pen.setWidth(playerWidth);
    p1->setPen(player1Pen);
    this->addItem(p1);
}
