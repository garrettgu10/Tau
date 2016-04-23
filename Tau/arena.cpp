#include "arena.h"
#include <QPainter>
#include <QGraphicsEllipseItem>

Arena::Arena()
{

}

void Arena::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
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
