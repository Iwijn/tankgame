#include "Map.h"
#include <random>

Map::Map(int width, int height) {
    this->width = width;
    this->height = height;
    this->horizontalWalls = new int[this->width * this->height];
    this->verticalWalls = new int[this->width * this->height];
    srand(timeSinceEpochMillisec());
}
Map::~Map() {
    delete[] this->horizontalWalls;
    delete[] this->verticalWalls;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS
///////////////////////////////////////////////////////////////////////////////////////////////////

void Map::clearMap() {
    for (auto i = 0; i < this->width * this->height; i++) {
        this->horizontalWalls[i] = 0;
        this->verticalWalls[i] = 0;
    }
}

void Map::setWall(GridPoint point, bool isHorizontal) {
    if (isHorizontal) {
        this->setHWall(point);
    } else {
        this->setVWall(point);
    }
}

void Map::setHWall(GridPoint point) {
    this->horizontalWalls[point.y*this->width + point.x] = 1;
}

void Map::setVWall(GridPoint point) {
    this->verticalWalls[point.y*this->width + point.x] = 1;
}

void Map::addBorders() {
    for (auto i = 0; i < this->width - 1; i++) {
        this->horizontalWalls[i] = 1;
        this->horizontalWalls[(this->height-1)*this->width + i] = 1;
    }
    for (auto i = 0; i < this->height - 1; i++) {
        this->verticalWalls[i*this->width] = 1;
        this->verticalWalls[i*this->width + this->width-1] = 1;
    }
}

GridPoint Map::getRandomStartPointOnBorder(Direction treeDirection) {
    switch (treeDirection) {
        case NORTH:
            return GridPoint {(int(random()) % (this->width-2) + 1), this->height-2};
        case EAST:
            return GridPoint {0, (int(random()) % (this->height-2) + 1)};
        case SOUTH:
            return GridPoint {(int(random()) % (this->width-2) + 1), 0};
        case WEST:
            return GridPoint {this->width-2, (int(random()) % (this->height-2) + 1)};
    }
}
GridPoint Map::getTreeStartPoint(Direction treeDirection) {
    GridPoint start;
    bool isHorizontal = directionIsHorizontal(treeDirection);
    int regenTries = 0;
    int maxRegenTries = 20;
    do {
        start = getRandomStartPointOnBorder(treeDirection);
        regenTries++;
    } while (this->nrOfOtherWallsTouching(start, isHorizontal) > 2 && regenTries < maxRegenTries);
    return start;
}


void Map::addRandomTreeStructure(GridPoint location, Direction direction) {
    // a wall starting from a border always has 2 walls (part of the border) touching it
    // if there are more than 2, then the start point of the tree will be touching another tree, so don't start the tree
    if (nrOfOtherWallsTouching(location, directionIsHorizontal(direction)) > 2) {
        return;
    }

    int i = 0;
    this->setWall(location, directionIsHorizontal(direction));
    while (i < 50) {
        int randomNum = random() % 5;
        switch (randomNum) {
            case 0:
                goLeft(location, direction);
                break;
            case 1:
                goRight(location, direction);
                break;
            default:
                goForward(location, direction);
                break;
        }
        i++;
    }
}

GridPoint forwardDeltas[4] = {
        {0, -1}, {1, 0}, {0, 1}, {-1, 0}
};
void Map::goForward(GridPoint &location, Direction direction) {
    GridPoint newWallLocation = location + forwardDeltas[direction];
    // going forward => direction stays the same
    bool isHorizontal = directionIsHorizontal(direction);
    if (this->wallExtensionIsPossible(newWallLocation, isHorizontal)) {
        this->setWall(newWallLocation, isHorizontal);
        location = newWallLocation;
    }
}

GridPoint turnLeftDeltas[4] = {
        {-1, 0}, {1, -1}, {0, 1}, {0, 0}
};
void Map::goLeft(GridPoint &location, Direction &direction) {
    GridPoint newWallLocation = location + turnLeftDeltas[direction];
    // current direction horizontal => vertical after turning left (and vice versa)
    bool isHorizontal = !directionIsHorizontal(direction);
    if (wallExtensionIsPossible(newWallLocation, isHorizontal)) {
        this->setWall(newWallLocation, isHorizontal);
        location = newWallLocation;
        --direction;
    }
}

GridPoint turnRightDeltas[4] = {
        {0, 0}, {1, 0}, {-1, 1}, {0, -1}
};
void Map::goRight(GridPoint &location, Direction &direction) {
    GridPoint newWallLocation = location + turnRightDeltas[direction];
    // current direction horizontal => vertical after turning right (and vice versa)
    bool isHorizontal = !directionIsHorizontal(direction);
    if (wallExtensionIsPossible(newWallLocation, isHorizontal)) {
        this->setWall(newWallLocation, isHorizontal);
        location = newWallLocation;
        ++direction;
    }
}

bool Map::wallExtensionIsPossible(GridPoint wallLocation, bool isHorizontal) {
    return this->nrOfOtherWallsTouching(wallLocation, isHorizontal) <= 1
           && this->wallWithinBorders(wallLocation, isHorizontal);
}

int Map::nrOfOtherWallsTouching(GridPoint point, bool isHorizontal) {
    if (isHorizontal) {
        return
            this->isVWall(point) +
            this->isHWall(GridPoint {point.x+1, point.y}) + this->isVWall(GridPoint {point.x+1, point.y}) +
            this->isVWall(GridPoint {point.x, point.y-1}) +
            this->isHWall(GridPoint {point.x-1, point.y}) +
            this->isVWall(GridPoint {point.x+1, point.y-1});
    } else {
        return
            this->isHWall(point) +
            this->isHWall(GridPoint {point.x, point.y+1}) + this->isVWall(GridPoint {point.x, point.y+1}) +
            this->isVWall(GridPoint {point.x, point.y-1}) +
            this->isHWall(GridPoint {point.x-1, point.y}) +
            this->isHWall(GridPoint {point.x-1, point.y+1});
    }
}

bool Map::wallWithinBorders(GridPoint point, bool isHorizontal) {
    if (isHorizontal) {
        return point.x >= 0 && point.x < this->width - 1 && point.y >= 1 && point.y < this->height-2;
    } else {
        return point.x >= 1 && point.x < this->width - 2 && point.y >= 0 && point.y < this->height-1;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS
///////////////////////////////////////////////////////////////////////////////////////////////////

bool Map::isHWall(GridPoint point) {
    if (point.x < 0 || point.x >= this->width || point.y < 0 || point.y >= this->height) {
        return false;
    }
    return this->horizontalWalls[point.y*this->width + point.x] == 1;
}

bool Map::isVWall(GridPoint point) {
    if (point.x < 0 || point.x >= this->width || point.y < 0 || point.y >= this->height) {
        return false;
    }
    return this->verticalWalls[point.y*this->width + point.x] == 1;
}


void Map::generateRandomMap() {
    clearMap();
    addBorders();

    // generate random horizontal walls
    // first row (y=0) is a horizontal border
    // last row (y=this->height-1) is a horizontal border
    // last column (x=this->width-1) is used for a vertical border
    for (auto x = 0; x < this->width - 1; x++) {
        for (auto y = 1; y < this->height - 1; y++) {
            if (random() % 5 == 0) {
                this->setHWall(GridPoint {x, y});
            }
        }
    }
    // generate random vertical walls
    // first column (x=0) is a vertical border
    // last column (x=this->width-1) is a vertical border
    // last row (y=this->height-1) is used for a horizontal border
    for (auto x = 1; x < this->width - 1; x++) {
        for (auto y = 0; y < this->height - 1; y++) {
            if (random() % 5 == 0) {
                this->setVWall(GridPoint {x, y});
            }
        }
    }
}

void Map::generateMap() {
    clearMap();
    addBorders();
    addRandomTreeStructure(getTreeStartPoint(NORTH), NORTH);
    addRandomTreeStructure(getTreeStartPoint(EAST), EAST);
    addRandomTreeStructure(getTreeStartPoint(SOUTH), SOUTH);
    addRandomTreeStructure(getTreeStartPoint(WEST), WEST);
    addRandomTreeStructure(getTreeStartPoint(NORTH), NORTH);
    addRandomTreeStructure(getTreeStartPoint(EAST), EAST);
    addRandomTreeStructure(getTreeStartPoint(SOUTH), SOUTH);
    addRandomTreeStructure(getTreeStartPoint(WEST), WEST);
}
