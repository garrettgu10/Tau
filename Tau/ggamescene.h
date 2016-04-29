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
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QRadialGradient>
#include <arena.h>
#include <scoredisplay.h>

class GGraphicsView;

class GGameScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GGameScene();
    void drawBoard();
    Player* p[2];
    Ball* b;
    int mostRecent;
    bool ongoing = true;
    QList<powerup*>* powerUps;
    void collectedPowerup(powerup* p);
    QSoundEffect* sizeUp;
    QSoundEffect* sizeDown;
    void gameOver();
    QMediaPlayer* music;
    QMediaPlaylist* playlist;
    ScoreDisplay* scores;

public slots:
    void updateGradBackground();
    void refresh();
    void addPowerUp();

private:
    Arena* box;
    void initGradBackground();
    QTimer* refresher;
    QRadialGradient* grad;
    QGraphicsRectItem* BgRect = new QGraphicsRectItem();
    QBrush* brush = new QBrush(QColor::fromRgb(255,255,255));
    QPen* arenaPen = new QPen(*brush,arenaWidth,Qt::SolidLine,Qt::SquareCap);
};

#endif // GGRAPHICSSCENE_H
