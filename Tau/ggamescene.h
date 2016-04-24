#ifndef GGRAPHICSSCENE_H
#define GGRAPHICSSCENE_H
#include <QGraphicsScene>
#include <math.h>
#include <player.h>
#include <ball.h>
#include <QTimer>
#include <QList>
#include <powerup.h>
#include <QSoundEffect>

class GGameScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GGameScene();
    void drawGradBackground();
    void drawBoard();
    Player* p[2];
    Ball* b;
    int mostRecent;
    bool ongoing = true;

    QList<powerup*>* powerUps;
    void collectedPowerup(powerup* p);
    QSoundEffect* sizeUp;
    QSoundEffect* sizeDown;

public slots:
    void refresh();
    void addPowerUp();

private:
    QTimer* ballUpdate;
    QBrush* brush = new QBrush(QColor::fromRgb(255,255,255));
    QPen* arenaPen = new QPen(*brush,arenaWidth,Qt::SolidLine,Qt::SquareCap);
};

#endif // GGRAPHICSSCENE_H
