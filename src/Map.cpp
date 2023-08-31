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
    GridPoint startPoint = getTreeStartPoint(SOUTH);
    addRandomTreeStructure(startPoint, SOUTH);
}

GridPoint Map::getTreeStartPoint(Direction treeDirection) {
    GridPoint start;
    switch (treeDirection) {
        case NORTH:
            start = GridPoint {(int(random()) % (this->width-2) + 1), this->height-2};
            this->setVWall(start);
            return start;
        case EAST:
            start = GridPoint {0, (int(random()) % (this->height-2) + 1)};
            this->setHWall(start);
            return start;
        case SOUTH:
            start = GridPoint {(int(random()) % (this->width-2) + 1), 0};
            this->setVWall(start);
            return start;
        case WEST:
            start = GridPoint {this->width-2, (int(random()) % (this->height-2) + 1)};
            this->setHWall(start);
            return start;
    }
}

void Map::addRandomTreeStructure(GridPoint location, Direction direction) {
    int i = 0;
    while (i < 15) {
        int randomNum = random() % 10;
        switch (randomNum) {
            case 5:
                goLeft(location, direction);
                break;
            case 6:
                goRight(location, direction);
                break;
            default:
                goForward(location, direction);
                break;
        }
        i++;
    }
}


void Map::goForward(GridPoint &location, Direction direction) {
    switch (direction) {
        case NORTH:
            location = GridPoint {location.x, location.y-1};
            this->setVWall(location);
            break;
        case EAST:
            location = GridPoint {location.x+1, location.y};
            this->setHWall(location);
            break;
        case SOUTH:
            location = GridPoint {location.x, location.y+1};
            this->setVWall(location);
            break;
        case WEST:
            location = GridPoint {location.x-1, location.y};
            this->setHWall(location);
            break;
    }
}

void Map::goLeft(GridPoint &location, Direction &direction) {
    switch (direction) {
        case NORTH:
            location = GridPoint {location.x-1, location.y};
            this->setHWall(location);
            direction = WEST;
            break;
        case EAST:
            location = GridPoint {location.x+1, location.y-1};
            this->setVWall(location);
            direction = NORTH;
            break;
        case SOUTH:
            location = GridPoint {location.x, location.y+1};
            this->setHWall(location);
            direction = EAST;
            break;
        case WEST:
            this->setVWall(location);
            direction = SOUTH;
            break;
    }
}

void Map::goRight(GridPoint &location, Direction &direction) {
    switch (direction) {
        case NORTH:
            this->setHWall(location);
            direction = EAST;
            break;
        case EAST:
            location = GridPoint {location.x+1, location.y};
            this->setVWall(location);
            direction = SOUTH;
            break;
        case SOUTH:
            location = GridPoint {location.x-1, location.y+1};
            this->setHWall(location);
            direction = WEST;
            break;
        case WEST:
            location = GridPoint {location.x, location.y-1};
            this->setVWall(location);
            direction = NORTH;
            break;
    }
}


bool Map::isHWall(GridPoint point) {
    if (DEBUG) {
        int x = point.x;
        int y = point.y;
        if (x < 0 || x >= this->width || y < 0 || y >= this->height) {
            std::cout << "ERROR: Map::isHWall(" << x << ", " << y << ") is out of bounds" << std::endl;
            return false;
        }
    }
    return this->horizontalWalls[point.y*this->width + point.x] == 1;
}

bool Map::isVWall(GridPoint point) {
    if (DEBUG) {
        int x = point.x;
        int y = point.y;
        if (x < 0 || x >= this->width || y < 0 || y >= this->height) {
            std::cout << "ERROR: Map::isVWall(" << x << ", " << y << ") is out of bounds" << std::endl;
            return false;
        }
    }
    return this->verticalWalls[point.y*this->width + point.x] == 1;
}
