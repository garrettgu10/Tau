#ifndef POWERUP_H
#define POWERUP_H
#include <QTimer>
#include <QGraphicsItem>
#include <QPointF>
#include <QPen>
#include <QBrush>

class powerup : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    powerup();
    void enable();
    void setPen(QPen pen);
    void setBrush(QBrush brush);
    QPointF* pos();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF rect();
    virtual QRectF boundingRect()const;

private:
    QPen pen;
    QBrush brush;
    int radius;
    QRectF* rekt;
    QTimer* thread;
    QPointF* position;
};

#endif // POWERUP_H
