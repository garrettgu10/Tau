#ifndef POWERUP_H
#define POWERUP_H
#include <QTimer>
#include <QGraphicsItem>
#include <QPointF>
#include <QPen>
#include <QBrush>
#include <constants.h>
#include <QImage>
#include <player.h>

class GGameScene;
class Ball;

class powerup : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    powerup(int id, GGameScene* parent);
    void setPen(QPen pen);
    QRectF rect();
    void setBrush(QBrush brush);
    QPointF* pos();
    powerUpType puptype();
    int rad();
    int id;
    bool enabled = false;

public slots:
    void enable();
    void disable();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QRectF boundingRect()const;

private:
    Player* affectedPlayer;
    double angle = 0;
    void keepRotating();
    double opacity = 0;
    void fadeIn();
    QImage* ico;
    GGameScene* parent;
    powerUpType t;
    QPen pen;
    QBrush brush;
    int radius;
    QRectF* rekt;
    QTimer* thread;
    QPointF* position;
};

#endif // POWERUP_H
