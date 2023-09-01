#pragma once
#include <iostream>

#include "util.h"

enum Direction {NORTH, EAST, SOUTH, WEST};

class Map {
private:
    int* horizontalWalls;
    int* verticalWalls;
    void clearMap();
    void addBorders();
    void setHWall(GridPoint point);
    void setVWall(GridPoint point);
    void setWall(GridPoint point, bool isHorizontal);
    void addRandomTreeStructure(GridPoint start, Direction direction);
    void goForward(GridPoint &location, Direction direction);
    void goLeft(GridPoint &location, Direction &direction);
    void goRight(GridPoint &location, Direction &direction);
    bool wallWithinBorders(GridPoint point, bool isHorizontal);
    int nrOfOtherWallsTouching(GridPoint point, bool isHorizontal);
    GridPoint getTreeStartPoint(Direction treeDirection);
    bool extendWallIfPossible(GridPoint point, bool isHorizontal, GridPoint &oldPoint);
    bool wallWithDirectionIsHorizontal(Direction direction);
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

