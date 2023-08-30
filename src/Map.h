#pragma once
#include <iostream>

#include "util.h"

class Map {
private:
    int* horizontalWalls;
    int* verticalWalls;
    void clearMap();
    void addBorders();
    void setHWall(GridPoint point);
    void setVWall(GridPoint point);
public:
    int width;
    int height;
    Map(int width, int height);
    ~Map();
    void generateRandomMap();
    void generateMap();
    bool isHWall(GridPoint point);
    bool isVWall(GridPoint point);
};
