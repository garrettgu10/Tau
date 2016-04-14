#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <QGraphicsItem>
#include <QPointF>

class Ball : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    QPointF* pos;
    Ball();
    int getRadius();
    QRectF* rect();
    void updateRect();
    void updatePos();
    virtual QRectF boundingRect() const;
protected:
    double angle = 0; // angle of motion in radians
    float speed;
    QRectF* rekt;
    int radius;
};

#endif // BALL_H
