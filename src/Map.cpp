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

GridPoint Map::getTreeStartPoint(Direction treeDirection) {
    GridPoint start;
    bool isHorizontal = this->wallWithDirectionIsHorizontal(treeDirection);
    int regenTries = 0;
    int maxRegenTries = 200;
    switch (treeDirection) {
        case NORTH:
            do {
                start = GridPoint {(int(random()) % (this->width-2) + 1), this->height-2};
                regenTries++;
            } while (this->nrOfOtherWallsTouching(start, isHorizontal) > 1 && regenTries < maxRegenTries);
            return start;
        case EAST:
            do {
                start = GridPoint {0, (int(random()) % (this->height-2) + 1)};
                regenTries++;
            } while (this->nrOfOtherWallsTouching(start, isHorizontal) > 1 && regenTries < maxRegenTries);
            return start;
        case SOUTH:
            do {
                start = GridPoint {(int(random()) % (this->width-2) + 1), 0};
                regenTries++;
            } while (this->nrOfOtherWallsTouching(start, isHorizontal) > 1 && regenTries < maxRegenTries);
            return start;
        case WEST:
            do {
                start = GridPoint {this->width-2, (int(random()) % (this->height-2) + 1)};
                regenTries++;
            } while (this->nrOfOtherWallsTouching(start, isHorizontal) > 1 && regenTries < maxRegenTries);
            return start;
    }
}


void Map::addRandomTreeStructure(GridPoint location, Direction direction) {
    // a wall starting from a border always has 2 walls (part of the border) touching it
    // if there are more than 2, then the start point of the tree will be touching another tree, so don't start the tree
    if (nrOfOtherWallsTouching(location, this->wallWithDirectionIsHorizontal(direction)) > 2) {
        return;
    }

    int i = 0;
    this->setWall(location, this->wallWithDirectionIsHorizontal(direction));
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

bool Map::extendWallIfPossible(GridPoint point, bool isHorizontal, GridPoint &oldPoint) {
    if (this->nrOfOtherWallsTouching(point, isHorizontal) > 1 || !this->wallWithinBorders(point, isHorizontal)) {
        return false;
    }
    this->setWall(point, isHorizontal);
    oldPoint = point;
    return true;
}

void Map::goForward(GridPoint &location, Direction direction) {
    bool isHorizontal = this->wallWithDirectionIsHorizontal(direction);
    switch (direction) {
        case NORTH:
            extendWallIfPossible(GridPoint {location.x, location.y-1}, isHorizontal, location);
            return;
        case EAST:
            extendWallIfPossible(GridPoint {location.x+1, location.y}, isHorizontal, location);
            return;
        case SOUTH:
            extendWallIfPossible(GridPoint {location.x, location.y+1}, isHorizontal, location);
            return;
        case WEST:
            extendWallIfPossible(GridPoint {location.x-1, location.y}, isHorizontal, location);
            return;
    }
}

void Map::goLeft(GridPoint &location, Direction &direction) {
    // if the wall is horizontal, then the new wall will be vertical and vice versa
    bool isHorizontal = !this->wallWithDirectionIsHorizontal(direction);
    switch (direction) {
        case NORTH:
            if (extendWallIfPossible(GridPoint {location.x-1, location.y}, isHorizontal, location)) {
                direction = WEST;
            }
            return;
        case EAST:
            if (extendWallIfPossible(GridPoint {location.x+1, location.y-1}, isHorizontal, location)) {
                direction = NORTH;
            }
            return;
        case SOUTH:
            if (extendWallIfPossible(GridPoint {location.x, location.y+1}, isHorizontal, location)) {
                direction = EAST;
            }
            return;
        case WEST:
            if (extendWallIfPossible(location, isHorizontal, location)) {
                direction = SOUTH;
            }
            return;
    }
}

void Map::goRight(GridPoint &location, Direction &direction) {
    // if the wall is horizontal, then the new wall will be vertical and vice versa
    bool isHorizontal = !this->wallWithDirectionIsHorizontal(direction);
    switch (direction) {
        case NORTH:
            if (extendWallIfPossible(location, isHorizontal, location)) {
                direction = EAST;
            }
            return;
        case EAST:
            if (extendWallIfPossible(GridPoint{location.x + 1, location.y}, isHorizontal, location)) {
                direction = SOUTH;
            }
            return;
        case SOUTH:
            if (extendWallIfPossible(GridPoint {location.x-1, location.y+1}, isHorizontal, location)) {
                direction = WEST;
            }
            return;
        case WEST:
            if (extendWallIfPossible(GridPoint {location.x, location.y-1}, isHorizontal, location)) {
                direction = NORTH;
            }
            return;
    }
}

bool Map::wallWithinBorders(GridPoint point, bool isHorizontal) {
    if (isHorizontal) {
        return point.x >= 0 && point.x < this->width - 1 && point.y >= 1 && point.y < this->height-2;
    } else {
        return point.x >= 1 && point.x < this->width - 2 && point.y >= 0 && point.y < this->height-1;
    }
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

bool Map::wallWithDirectionIsHorizontal(Direction direction) {
    return direction == EAST || direction == WEST;
}
