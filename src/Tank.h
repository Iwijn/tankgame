#pragma once
#include "util.h"
#include "debug.h"
#include <cmath>
#include <vector>
#include "GameState.h"

class GameState;

class Tank {
public:
    explicit Tank(GameState &gameState);
    void moveIfPossible(float distance);
    void rotateIfPossible(float degrees);

    Point getMiddlePoint();
    Point getTopLeftCorner();
    Point getTopRightCorner();
    Point getBottomLeftCorner();
    Point getBottomRightCorner();

    float getXPos();
    void setXPos(float xPos);
    float getYPos();
    void setYPos(float yPos);
    float getWidth();
    void setWidth(float width);
    float getHeight();
    void setHeight(float height);
    float getRotation();
    void setRotation(float rotation);
private:
    GameState &gameState;
    float xPos;
    float yPos;
    float width;
    float height;
    float rotation;

    bool isColliding();
    bool isTank(Point point);
    void getCollisionZoneGridPoints(std::list<GridPoint>& gridPoints);
    void move(float distance);
    void rotate(float degrees);

};
