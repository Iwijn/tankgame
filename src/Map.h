#pragma once
#include <iostream>

#include "util.h"

class Map {
private:
    int* horizontalWalls;
    int* verticalWalls;
    void clearMap();
    void addBorders();
    void setWall(GridPoint point, bool isHorizontal);
    void setHWall(GridPoint point);
    void setVWall(GridPoint point);
    GridPoint getRandomStartPointOnBorder(Direction treeDirection);
    GridPoint getTreeStartPoint(Direction treeDirection);
    void addRandomTreeStructure(GridPoint start, Direction direction);
    void goForward(GridPoint &location, Direction direction);
    void goLeft(GridPoint &location, Direction &direction);
    void goRight(GridPoint &location, Direction &direction);
    bool wallExtensionIsPossible(GridPoint wallLocation, bool isHorizontal);
    bool wallWithinBorders(GridPoint point, bool isHorizontal);
    int nrOfOtherWallsTouching(GridPoint point, bool isHorizontal);
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

