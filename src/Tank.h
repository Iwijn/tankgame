#ifndef TANKGAME_TANK_H
#define TANKGAME_TANK_H

#include "util.h"
#include <cmath>

class Tank {
public:
    float xPos;
    float yPos;
    float width;
    float height;
    float rotation;
    Tank(float width, float height);
    Point getTopLeftCorner();
    Point getTopRightCorner();
    Point getBottomLeftCorner();
    Point getBottomRightCorner();
    Point rotatePoint(Point p);
};


#endif //TANKGAME_TANK_H
