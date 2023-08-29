#include <iostream>
#include "GameState.h"
#include "util.h"
#include "debug.h"

GameState::GameState(int gridSize, int wallThickness, float defaultTankWidth, float defaultTankHeight): map(10, 10) {
    this->tanks = std::list<Tank*>();
    this->prevLoopTime=timeSinceEpochMillisec();
    this->gridSize=gridSize;
    this->wallThickness=wallThickness;
    this->defaultTankWidth=defaultTankWidth;
    this->defaultTankHeight=defaultTankHeight;
    this->map.generateMap();
}

GridPoint GameState::getGridPoint(Point point) {
    return GridPoint {
        (int) point.x / this->gridSize, (int) point.y / this->gridSize
    };
}

bool GameState::isWall(Point point) {
    // position of the square that contains point (x,y) in the grid
    GridPoint gridPoint = getGridPoint(point);

    // if there is no horizontal or vertical wall in the square, then there is no wall
    if (!this->map.isHWall(gridPoint) && !this->map.isVWall(gridPoint)) {
        return false;
    }

    // coordinates of point (x,y) inside the square. (0,0) being the top left corner of the square
    float inGridX = std::fmod(point.x, (float) this->gridSize);
    float inGridY = std::fmod(point.y, (float) this->gridSize);


    // the horizontal wall of a square is at the top of the square
    if (this->map.isHWall(gridPoint) && inGridY < this->wallThickness) {
        return true;
    }
    // the vertical wall of a square is at the left of the square
    if (this->map.isVWall(gridPoint) && inGridX < this->wallThickness) {
        return true;
    }

    return false;
}

void GameState::getCornerPointsOfWalls(std::list<Point>& cornerPoints, GridPoint gridPoint) {
    if (this->map.isHWall(gridPoint)) {
        // top left corner
        cornerPoints.push_back(Point {float(gridPoint.x * this->gridSize), float(gridPoint.y * this->gridSize)});
        // top right corner
        cornerPoints.push_back(Point {float(gridPoint.x * this->gridSize + gridSize - 1), float(gridPoint.y * this->gridSize)});
        // bottom right corner
        cornerPoints.push_back(Point {float(gridPoint.x * this->gridSize + gridSize - 1), float(gridPoint.y * this->gridSize + wallThickness - 1)});
        // bottom left corner
        cornerPoints.push_back(Point {float(gridPoint.x * this->gridSize), float(gridPoint.y * this->gridSize + wallThickness - 1)});
    }
    if (this->map.isVWall(gridPoint)) {
        // top left corner
        cornerPoints.push_back(Point {float(gridPoint.x * this->gridSize), float(gridPoint.y * this->gridSize)});
        // top right corner
        cornerPoints.push_back(Point {float(gridPoint.x * this->gridSize + wallThickness - 1), float(gridPoint.y * this->gridSize)});
        // bottom right corner
        cornerPoints.push_back(Point {float(gridPoint.x * this->gridSize + wallThickness - 1), float(gridPoint.y * this->gridSize + gridSize - 1)});
        // bottom left corner
        cornerPoints.push_back(Point {float(gridPoint.x * this->gridSize), float(gridPoint.y * this->gridSize + gridSize - 1)});
    }

    // TODO: these corners can be reduced when there is a horizontal and vertical wall

    if (DEBUG) Debug::GetInstance()->drawWallCornerPoints(cornerPoints);
}
