#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <QGraphicsItem>
#include <QPointF>

class Ball : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    QPointF* pos;
    Ball();
    int getRadius();
    QRectF* rect();
    void updateRect();
protected:
    virtual QRectF boundingRect();
    int angle; // angle of motion in 16ths of degrees
    float speed;
    QRectF* rekt;
    int radius;
};

#endif // BALL_H
