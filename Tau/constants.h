#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QPointF>

enum class powerUpType{sizeUp=0,
                       NUM_POWERUPTYPES};

const int refreshInterval = 23;
const int windowWidth = 750;//width of window
const int windowHeight = 750; //height of window
const int playerWidth = 15; //width of paddle
const int arenaWidth = 5; //width of arena circle
const int arenaRadius = windowHeight/2*.9; //radius of arena circle
const int playerInitSize = 180; //in 16ths of degrees (angular difference from center to side of paddle)
const int playerRadius = arenaRadius-playerWidth-arenaWidth/2; //radius of circle in which the paddles are drawn
const int ballInitRadius = 10; //the ball's initial radius
const double ballInitSpeed = 7; //ball's initial speed
const int powerUpRadius = 15; //radius of a powerup

#endif // CONSTANTS_H
