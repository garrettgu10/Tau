#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QPointF>
#include <QString>

enum class powerUpType{ballSizeUp=0,paddleSizeUp,paddleSizeDown,arrow,warp,lightning,wobble,random,ghost,snail,
                       NUM_POWERUPTYPES};
const QString icos[(int)powerUpType::NUM_POWERUPTYPES] = {":/ico/sizeUp.png",
        ":/ico/add.png",
        ":/ico/minus.png",
        ":/ico/arrowRight.png",
        ":/ico/warp.png",
        ":/ico/lightning.png",
        ":/ico/wobble.png",
        ":/ico/random.png",
        ":/ico/ghost.png",
        ":/ico/snail.png"};
const bool powerupExtendable[(int)powerUpType::NUM_POWERUPTYPES] =
        {false, false, false, false, true, false, true, false, true, false};

const int numSongs = 2;
const QString songs[numSongs] = {"Overriding Concern","Proof_of_Concept"};
const int BPM[numSongs] = {120,140};

const int refreshInterval = 20; //time between frame refreshes
const int windowWidth = 900; //width of window
const int windowHeight = 750; //height of window
const int playerWidth = 15; //width of paddle
const int arenaWidth = 5; //width of arena circle
const int arenaRadius = windowHeight/2*.9; //radius of arena circle
const int mainMenuArenaRadius = arenaRadius/3; //main menu circle radius
const int playerInitSize = 180; //in 16ths of degrees (angular difference from center to side of paddle)
const int playerRadius = arenaRadius-playerWidth-arenaWidth/2; //radius of circle in which the paddles are drawn
const int ballInitRadius = 10; //the ball's initial radius
const double ballInitSpeed = 9.5; //ball's initial speed
const int powerUpRadius = 20; //radius of a powerup
const int powerUpInterval = 3000; //in ms; amount of time between powerups added
const int powerUpEnabledTime = 10000; //how long a powerup lasts
const int powerUpAvailableTime = 15000; //how long a powerup is available for pickup
const int playButtonSize = mainMenuArenaRadius*0.6; //main menu playbutton size (dist from center to any point)

#endif // CONSTANTS_H
