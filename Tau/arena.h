#ifndef ARENA_H
#define ARENA_H
#include <QPainter>
#include <QGraphicsEllipseItem>
#include <constants.h>
#include <helper.h>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

class Arena : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Arena();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*);
    void setPen(const QPen &pen);
    void setRadius(int rad);
    int permRadius = arenaRadius;
    int radius = permRadius;
    void startPulse(int bpm);
    void setPermRadius(int prad);
    QRadialGradient* grad = new QRadialGradient(windowWidth/2,windowHeight/2, arenaRadius/0.9);
    int pulseDist = 10;
    QTimer* updateBg;
    QGraphicsRectItem* bkg;

signals:
    void pulsed();

public slots:
    void pulse();
    void changeBPM(int i);

private:
    QPen* clear = new QPen(QColor(0,0,0,0));
    QPen* bluePen;
    QPen* redPen;
};

#endif // ARENA_H
