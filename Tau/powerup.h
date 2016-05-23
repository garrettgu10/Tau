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
    virtual QRectF boundingRect()const;

public slots:
    void enable();
    void disable();
    void rotate();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*);

private:
    bool disabled = false;
    QTimer* rotator;
    QTimer* disabler;
    Player* affectedPlayer;
    int angle = 0; // in degrees
    double opacity = 0;
    void fadeIn();
    QImage* ico;
    GGameScene* parent;
    powerUpType pupType;
    QPen pen;
    QBrush brush;
    int radius;
    QRectF* rekt;
    QTimer* thread;
    QPointF* position;
};

#endif // POWERUP_H
