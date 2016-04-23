#ifndef ARENA_H
#define ARENA_H
#include <QPainter>
#include <QGraphicsEllipseItem>

class Arena : public QGraphicsEllipseItem
{
public:
    Arena();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setPen(const QPen &pen);

private:
    QPen* bluePen;
    QPen* redPen;
};

#endif // ARENA_H
