#include "Tank.h"

Tank::Tank(float width, float height) {
    this->xPos=35;
    this->yPos=35;
    this->width=width;
    this->height=height;
    this->rotation=0;
}

Point Tank::getTopLeftCorner() {
    struct Point point {
        xPos - width/2, yPos - height/2
    };
    return rotatePoint(point);
}
Point Tank::getTopRightCorner() {
    struct Point point {
            xPos + width/2, yPos - height/2
    };
    return rotatePoint(point);
}
Point Tank::getBottomLeftCorner() {
    struct Point point {
            xPos - width/2, yPos + height/2
    };
    return rotatePoint(point);
}
Point Tank::getBottomRightCorner() {
    struct Point point {
            xPos + width/2, yPos + height/2
    };
    return rotatePoint(point);
}

Point Tank::rotatePoint(Point point)
{
    float angle = this->rotation * M_PI / 180;
    float s = std::sin(angle);
    float c = std::cos(angle);

    // translate point to origin:
    float originX = point.x - this->xPos;
    float originY = point.y - this->yPos;

    // rotate point, add origin coord back
    return Point {
        this->xPos + (originX * c - originY * s), this->yPos + (originX * s + originY * c)
    };
}
