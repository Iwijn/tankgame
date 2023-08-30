#include "Map.h"
#include <random>

Map::Map(int width, int height) {
    this->width = width;
    this->height = height;
    this->horizontalWalls = new int[this->width * this->height];
    this->verticalWalls = new int[this->width * this->height];
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
