#include "scoredisplay.h"
#include <QPainter>

ScoreDisplay::ScoreDisplay()
{
    scores[0] = 0;
    scores[1] = 0;
}

int ScoreDisplay::getScore(int playerNum)
{
    return scores[playerNum];
}

QRectF ScoreDisplay::boundingRect() const
{
    return QRectF(0,0,windowWidth,windowHeight);
}

void ScoreDisplay::setPen(QPen pen)
{
    this->pen = pen;
    this->pen.setColor(QColor::fromRgb(255,255,255,128));
}

void ScoreDisplay::setBrush(QBrush brush)
{
    this->brush = brush;
}

void ScoreDisplay::score(int playerNum)
{
    scores[playerNum]++;
}

void ScoreDisplay::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    int ballHeight = ballInitRadius+padding*2;
    int height0 = ballHeight*scores[0];
    painter->setPen(pen);
    painter->setBrush(brush);
    for(int i = 0; i < scores[0];i++){
        painter->drawEllipse(QPointF((windowWidth/2-arenaRadius)/2,
                                     windowHeight/2-height0/2+padding+ballInitRadius+ballHeight*i),
                             ballInitRadius,ballInitRadius);
    }
    int height1 = ballHeight*scores[1];
    for(int i = 0; i < scores[1];i++){
        painter->drawEllipse(QPointF(windowWidth-(windowWidth/2-arenaRadius)/2,
                                     windowHeight/2-height1/2+padding+ballInitRadius+ballHeight*i),
                             ballInitRadius,ballInitRadius);
    }
}
