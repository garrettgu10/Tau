#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <QGraphicsItem>
#include <QPointF>
#include <QPen>
#include <QBrush>
#include <constants.h>
#include <player.h>
#include <QPainterPath>
#include <powerup.h>

class GGameScene;

class Ball : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    QPointF* pos;
    Ball(GGameScene* parent);
    int getRadius();
    QRectF* rect();
    void updateRect();
    void setPen(QPen pen);
    void setBrush(QBrush brush);
    virtual QRectF boundingRect() const;
    int setrad(int r);

public slots:
    void updatePos();
    void sizeUp();
    void sizeDown();

protected:
    int angle = 0; // angle of motion in 160ths of degrees
    double speed;
    QRectF* rekt;

    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
private:
    void bounce(Player *p, int pdiff, int angleWithCenter);
    int radius;
    void collision();
    GGameScene* parent;
    Player* p1;
    Player* p2;
    QPen pen;
    QBrush brush;
    bool bouncing = false;
};

#endif // BALL_H
