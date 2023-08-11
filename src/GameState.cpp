#include "GameState.h"
#include "util.h"

GameState::GameState() {
    this->tanks = std::list<Tank>();
    this->prevLoopTime=timeSinceEpochMillisec();
}
