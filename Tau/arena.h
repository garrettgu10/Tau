#ifndef ARENA_H
#define ARENA_H
#include <QPainter>
#include <QGraphicsEllipseItem>
#include <constants.h>
#include <helper.h>

class Arena : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Arena();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*);
    void setPen(const QPen &pen);
    void setRadius(int rad);
    int radius = arenaRadius;
    QBrush* gradBrush;
    QRadialGradient* grad = new QRadialGradient(windowWidth/2,windowHeight/2, windowHeight/2);

public slots:
    void pulse();

private:
    QPen* clear = new QPen(QColor(0,0,0,0));
    QPen* bluePen;
    QPen* redPen;
};

#endif // ARENA_H
