#include "titletext.h"

titleText::titleText(QPointF* center, int size, QString text)
{
    this->text = text;
    textFont = new QFont("Times New Roman",size,QFont::Normal,false);
    this->center = center;
    this->opacity = 1.0;
    fontMetrics = new QFontMetrics(QFont(*textFont));
}

QRectF titleText::boundingRect() const
{
    return QRectF(center->x()-size,center->y()-size,size*2,size*2);
}

void titleText::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(QColor::fromRgb(255,255,255));
    painter->setBrush(QBrush(QColor::fromRgb(255,255,255)));
    painter->setFont(*textFont);
    painter->setOpacity(opacity);
    painter->translate(center->x()-fontMetrics->width(text)/2,center->y());
    painter->drawText(0,0,text);
}
