#ifndef CONSTANTS_H
#define CONSTANTS_H

enum class collisionType{none, p1, p2};

const int windowWidth = 1450;//width of window
const int windowHeight = 750; //height of window
const int playerWidth = 15; //width of paddle
const int arenaWidth = 5; //width of arena circle
const int arenaRadius = windowHeight/2*.8; //radius of arena circle
const int playerRadius = arenaRadius-playerWidth/2-arenaWidth/2; //radius of circle in which the paddles are drawn
const int ballInitRadius = 10; //the ball's initial radius

#endif // CONSTANTS_H
