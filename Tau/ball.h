#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <QGraphicsItem>
#include <QPointF>
#include <QPen>
#include <QBrush>
#include <constants.h>

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
    void setPen(QPen pen);
    void setBrush(QBrush brush);
    virtual QRectF boundingRect() const;
protected:
    double angle = 0; // angle of motion in radians
    float speed;
    QRectF* rekt;
    int radius;
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
private:
    QPen pen;
    QBrush brush;
};

#endif // BALL_H
