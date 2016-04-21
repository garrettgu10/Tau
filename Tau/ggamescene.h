#ifndef GGRAPHICSSCENE_H
#define GGRAPHICSSCENE_H
#include <QGraphicsScene>
#include <math.h>
#include <player.h>
#include <ball.h>
#include <QTimer>
#include <QList>
#include <powerup.h>

class GGameScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GGameScene();
    void drawGradBackground();
    void drawBoard();
    Player* p1;
    Ball* b;
    Player* p2;
    Player* mostRecent;
    bool ongoing = true;

    QList<powerup*>* powerUps;
    void collectedPowerup(powerup* p);

public slots:
    void addPowerUp();

private:
    QTimer* ballUpdate;
    QBrush* brush = new QBrush(QColor::fromRgb(255,255,255));
    QPen* arenaPen = new QPen(*brush,arenaWidth,Qt::SolidLine,Qt::RoundCap);
};

#endif // GGRAPHICSSCENE_H
