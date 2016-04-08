#ifndef GGRAPHICSSCENE_H
#define GGRAPHICSSCENE_H
#include <QGraphicsScene>
#include <math.h>
#include <player.h>

class GGraphicsScene : public QGraphicsScene
{
public:
    GGraphicsScene();
    void drawGradBackground();
    void drawBoard();

private:
    double arenaRadius;

    Player* p1;
    Player* p2;
};

#endif // GGRAPHICSSCENE_H
