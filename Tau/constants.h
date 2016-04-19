#ifndef CONSTANTS_H
#define CONSTANTS_H

enum class powerUpType{sizeUp=0,
                       NUM_POWERUPTYPES};

const int windowWidth = 1450;//width of window
const int windowHeight = 750; //height of window
const int playerWidth = 15; //width of paddle
const int arenaWidth = 5; //width of arena circle
const int arenaRadius = windowHeight/2*.9; //radius of arena circle
const int playerRadius = arenaRadius-playerWidth-arenaWidth/2; //radius of circle in which the paddles are drawn
const int ballInitRadius = 10; //the ball's initial radius
const double ballInitSpeed = 8;
const int powerUpRadius = 10;

#endif // CONSTANTS_H
