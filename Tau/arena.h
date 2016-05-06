#ifndef ARENA_H
#define ARENA_H
#include <QPainter>
#include <QGraphicsEllipseItem>
#include <constants.h>
#include <helper.h>
#include <QTimer>

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
    QBrush* gradBrush;
    QRadialGradient* grad = new QRadialGradient(windowWidth/2,windowHeight/2, permRadius/0.9);
    void startPulse(int bpm);
    void setPermRadius(int prad);
    int pulseDist = 10;
    QTimer* updateBg;

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
