#ifndef GGRAPHICSSCENE_H
#define GGRAPHICSSCENE_H
#include <QGraphicsScene>
#include <math.h>
#include <player.h>
#include <ball.h>
#include <QTimer>

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
private:
    QTimer* ballUpdate;
};

#endif // GGRAPHICSSCENE_H
