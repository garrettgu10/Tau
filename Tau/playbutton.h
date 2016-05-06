#ifndef PLAYBUTTON_H
#define PLAYBUTTON_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <math.h>
#include <constants.h>

class playButton : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    playButton(int size);
    virtual QRectF boundingRect() const;
    void setBrush(QBrush* brush);
    void setPen(QPen* pen);
    void incrementAngle();
    void setSize(int size);
    int getSize();
    int permSize;

public slots:
    void pulse();

protected:
    void paint (QPainter * painter, const QStyleOptionGraphicsItem*, QWidget*);

private:
    int size;
    QBrush* brush;
    QPen* pen;
    QPointF points[3];
    void setPoints(int size);
    int angle = 0; //in degrees
};

#endif // PLAYBUTTON_H
