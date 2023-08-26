#ifndef TANKGAME_TANK_H
#define TANKGAME_TANK_H

#include "util.h"
#include <cmath>
#include "GameState.h"

class GameState;

class Tank {
public:
    GameState &gameState;
    explicit Tank(GameState &gameState);
    Point getTopLeftCorner();
    Point getTopRightCorner();
    Point getBottomLeftCorner();
    Point getBottomRightCorner();
    Point rotatePoint(Point p);
    void move(float distance);
    bool isColliding();
    void moveIfPossible(float distance);
    void rotate(float degrees);

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
    float xPos;
    float yPos;
    float width;
    float height;
    float rotation;
};


#endif //TANKGAME_TANK_H
