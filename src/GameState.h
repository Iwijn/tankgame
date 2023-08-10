#ifndef TANKGAME_GAMESTATE_H
#define TANKGAME_GAMESTATE_H

#include "util.h"

class GameState {
public:
    float xPos;
    float yPos;
    uint64_t prevLoopTime;
    GameState();
};


#endif //TANKGAME_GAMESTATE_H
