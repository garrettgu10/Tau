#ifndef GGRAPHICSSCENE_H
#define GGRAPHICSSCENE_H
#include <QGraphicsScene>
#include <math.h>
#include <player.h>
#include <ball.h>
#include <QTimer>
#include <QList>
#include <powerup.h>

class GGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GGraphicsScene();
    void drawGradBackground();
    void drawBoard();
    Player* p1;
    Ball* b;
    Player* p2;
    void addPowerUp();

private:
    QList<powerup*>* powerUps;
    QTimer* ballUpdate;
    QBrush* brush = new QBrush(QColor::fromRgb(255,255,255));
    QPen* arenaPen = new QPen(*brush,arenaWidth,Qt::SolidLine,Qt::RoundCap);
};

#endif // GGRAPHICSSCENE_H
