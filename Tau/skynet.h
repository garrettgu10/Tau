#ifndef SKYNET_H
#define SKYNET_H

#include <QObject>

class Ball;
class Player;

class skynet : public QObject
{
    Q_OBJECT
public:
    skynet(Ball *b, Player *p);

signals:

public slots:
    void act();

private:
    Ball* ball;
    Player* player;
};

#endif // SKYNET_H
