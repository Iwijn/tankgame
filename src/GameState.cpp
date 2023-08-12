#include "GameState.h"
#include "util.h"

GameState::GameState() {
    this->tanks = std::list<Tank>();
    this->prevLoopTime=timeSinceEpochMillisec();
}

bool GameState::isWall(float x, float y) {
    // position of the square that contains point (x,y) in the grid
    int gridX = ((int) x) / this->gridSize;
    int gridY = ((int) y) / this->gridSize;

    // if there is no horizontal or vertical wall in the square, then there is no wall
    if (!this->horizontalWalls[gridY][gridX] && !this->verticalWalls[gridY][gridX]) {
        return false;
    }

    // coordinates of point (x,y) inside the square. (0,0) being the top left corner of the square
    float inGridX = std::fmod(x, (float) this->gridSize);
    float inGridY = std::fmod(y, (float) this->gridSize);

    // the horizontal wall of a square is at the top of the square
    if (this->horizontalWalls[gridY][gridX] && inGridY < this->wallThickness) {
        return true;
    }
    // the vertical wall of a square is at the left of the square
    if (this->verticalWalls[gridY][gridX] && inGridX < this->wallThickness) {
        return true;
    }

    return false;
}
