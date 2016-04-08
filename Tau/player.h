#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsEllipseItem>

class Player : public QGraphicsEllipseItem
{
public:
    Player(double pos, double size);
    double pos; // angular position
    double size; // angular distance from center to edge
protected:
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
};

#endif // PLAYER_H
