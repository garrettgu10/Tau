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
#include <QSoundEffect>

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
    void setrad(int r);
    void setAngle(int angle);
    void explode();
    bool disabled = false;

    QTimer* warper;
    QTimer* wobbler;
    void startGhost();
    void stopGhost();
    double getSpeed();
    bool setSpeed(double newSpeed);
    void startWobble();

public slots:
    void setup();
    void wobble();
    void warpToggleSpeeds();
    void updatePos();
    void sizeUp();
    void sizeDown();
    void setBouncingToFalse();
    void ghostUpdate();

protected:
    int angle = 0; // angle of motion in 16ths of degrees
    QRectF* rekt;
    void paint (QPainter * painter, const QStyleOptionGraphicsItem*, QWidget*);

private:
    void updateImpactAngle();
    void updateImpactPoint();
    QPointF impactPoint;
    int impactAngle = 0; // angle at which ball will collide with arena (16ths of degrees)
    int permAngle;
    double speed;
    bool goingBrighter = false;
    QTimer* ghoster;
    double arrowLength = 0;
    bool drawArrow = false;
    void initSpin();
    bool spedUp = false;
    bool warpSpedUp = false;
    double opacity = 1.0;
    void bounce(Player *p, int pdiff, int angleWithCenter);
    int radius;
    void checkCollision();
    GGameScene* parent;
    Player* p[2];
    QPen pen;
    QBrush brush;
    bool bouncing = false;
};

#endif // BALL_H
