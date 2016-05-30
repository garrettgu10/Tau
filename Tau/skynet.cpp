#include "skynet.h"

#include <ball.h>
#include <player.h>
#include <constants.h>
#include <math.h>

skynet::skynet(Ball* b, Player* p,int playerNum)
{
    ball = b;
    player = p;
}

void skynet::act()
{
    if(playerNum==0){
        if(ball->getImpactAngle() < 1440 || ball->getImpactAngle() > 4320)
            return;

        if(abs(ball->getImpactAngle()-player->pos) < paddleStepSize)
            return;

        if(ball->getImpactAngle() < player->pos){
            player->moveCClockwise();
        }else{
            player->moveClockwise();
        }
    }
}
