#include "GameState.h"
#include "util.h"

GameState::GameState() {
    this->xPos=0;
    this->yPos=0;
    this->prevLoopTime=timeSinceEpochMillisec();
}
