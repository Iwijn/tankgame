#include <iostream>
#include "GameState.h"
#include "util.h"

GameState::GameState(int gridSize, int wallThickness) {
    this->tanks = std::list<Tank>();
    this->prevLoopTime=timeSinceEpochMillisec();
    this->gridSize=gridSize;
    this->wallThickness=wallThickness;
}

bool GameState::isWall(Point point) {
    // position of the square that contains point (x,y) in the grid
    int gridX = ((int) point.x) / this->gridSize;
    int gridY = ((int) point.y) / this->gridSize;

    // if there is no horizontal or vertical wall in the square, then there is no wall
    if (!this->horizontalWalls[gridY][gridX] && !this->verticalWalls[gridY][gridX]) {
        return false;
    }

    // coordinates of point (x,y) inside the square. (0,0) being the top left corner of the square
    float inGridX = std::fmod(point.x, (float) this->gridSize);
    float inGridY = std::fmod(point.y, (float) this->gridSize);


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
