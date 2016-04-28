#ifndef ARENA_H
#define ARENA_H
#include <QPainter>
#include <QGraphicsEllipseItem>
#include <constants.h>

class Arena : public QGraphicsEllipseItem
{
public:
    Arena();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setPen(const QPen &pen);
    void setRadius(int rad);
    int radius = arenaRadius;

private:
    QPen* bluePen;
    QPen* redPen;
};

#endif // ARENA_H
