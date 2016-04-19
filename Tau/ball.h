#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <QGraphicsItem>
#include <QPointF>
#include <QPen>
#include <QBrush>
#include <constants.h>
#include <player.h>

class Ball : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    QPointF* pos;
    Ball(Player* p1, Player* p2);
    int getRadius();
    QRectF* rect();
    void updateRect();
    void setPen(QPen pen);
    void setBrush(QBrush brush);
    virtual QRectF boundingRect() const;

public slots:
    void updatePos();
protected:
    int angle = 0; // angle of motion in 160ths of degrees
    double speed;
    QRectF* rekt;
    int radius;
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
private:
    void collision();
    Player* p1;
    Player* p2;
    QPen pen;
    QBrush brush;
    bool bouncing = false;
};

#endif // BALL_H
