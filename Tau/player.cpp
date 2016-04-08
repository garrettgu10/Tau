#include "player.h"
#include <QPainter>

Player::Player(double pos, double size)
{
    this->pos = pos;
    this->size = size;
}
void Player::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) {
        painter->setPen(pen());
        painter->setBrush(brush());
        painter->drawArc(rect(), startAngle(), spanAngle());
}
