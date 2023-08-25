#ifndef TANKGAME_GAMESTATE_H
#define TANKGAME_GAMESTATE_H

#include <list>
#include <cmath>
#include "util.h"
#include "Tank.h"

class Tank;

class GameState {
public:
    std::list<Tank*> tanks;
    uint64_t prevLoopTime;
    int gridSize;
    int wallThickness;
    GameState(int gridSize, int wallThickness);
    bool isWall(Point point);
    int horizontalWalls4[4][4] = {
            {1, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {1, 1, 1, 1}
    };
    int verticalWalls4[4][4] = {
            {1, 0, 0, 1},
            {1, 0, 0, 1},
            {1, 0, 0, 1},
            {1, 0, 0, 1}
    };
    int horizontalWalls[10][10] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, // 0
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 1
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 2
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 3
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 4
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 6
            {1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, // 5
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 7
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 8
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 0}  // 9
    };
    int verticalWalls[10][10] = {
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, // 0
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, // 1
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, // 2
            {1, 0, 0, 0, 1, 0, 0, 0, 0, 1}, // 3
            {1, 0, 0, 0, 1, 0, 0, 0, 0, 1}, // 4
            {1, 0, 0, 0, 1, 0, 0, 0, 0, 1}, // 5
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, // 6
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, // 7
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, // 8
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // 9
    };
};


#endif //TANKGAME_GAMESTATE_H
