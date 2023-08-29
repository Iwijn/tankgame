#pragma once
#include <iostream>

#include "util.h"

class Map {
private:
    int* horizontalWalls;
    int* verticalWalls;
public:
    int width;
    int height;
    Map(int width, int height);
    ~Map();
    void generateMap();
    bool isHWall(GridPoint point);
    bool isVWall(GridPoint point);
};
