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
#include <titletext.h>
#include <settings.h>

class GGraphicsView;

class GGameScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GGameScene(Arena *box, Settings *settingsmgr);
    void drawBoard();
    Player* p[2];
    Ball* ball;
    int mostRecent;
    bool ongoing = true;
    QList<powerup*>* powerUps;
    void collectedPowerup(powerup* p);
    void gameOver();
    ScoreDisplay* scores;
    int overlappingPups[(int)powerUpType::NUM_POWERUPTYPES];
    int winningScore = 3;
    int winner = -1;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void exitSequence();
    Arena* box;

signals:
    void doneExiting();
    void endingTriggered();

public slots:
    void refresh();
    void addPowerUp();

private:
    bool endingTrigger = false;
    Settings* settingsmgr;
    void win(int winner);
    titleText* winnerText;
    QTimer* addPowerUps;
    QRadialGradient* grad;
    QGraphicsRectItem* BgRect = new QGraphicsRectItem();
    QBrush* brush = new QBrush(QColor::fromRgb(255,255,255));
    QPen* arenaPen = new QPen(*brush,arenaWidth,Qt::SolidLine,Qt::SquareCap);
};

#endif // GGRAPHICSSCENE_H
