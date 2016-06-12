#include "skynet.h"

#include <ball.h>
#include <player.h>
#include <constants.h>
#include <qdebug.h>
#include <math.h>

skynet::skynet(Ball* b, Player* p)
{
    ball = b;
    player = p;
}

void skynet::act()
{
    if(ball->getOpacity() < 0.15)
        return;

    int impactAngle = ball->getImpactAngle();
    int playerPos = player->pos;

    if(impactAngle > 4320){
        impactAngle-=5760;
    }

    if(player->playerNum==0){
        if((impactAngle < 1440 || impactAngle > 4320) && !ball->wobbling)
            return;
    }else{
        if((impactAngle <-1440 || impactAngle > 1440) && !ball->wobbling)
            return;
    }

    if(abs(impactAngle-playerPos) < paddleStepSize)
        return;

    if(impactAngle < playerPos){
        player->moveCClockwise();
    }else{
        player->moveClockwise();
    }
}
