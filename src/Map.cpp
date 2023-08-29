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

void Map::generateMap() {
    for (auto i = 0; i < this->width * this->height; i++) {
        this->horizontalWalls[i] = 0;
        this->verticalWalls[i] = 0;
    }

    // generate random horizontal walls
    for (auto i = 0; i < this->width * this->height; i++) {
        if (random() % 5 == 0) {
            this->horizontalWalls[i] = 1;
        }
    }
    // generate random vertical walls
    for (auto i = 0; i < this->width * this->height; i++) {
        if (random() % 5 == 0) {
            this->verticalWalls[i] = 1;
        }
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
