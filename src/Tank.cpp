#include <iostream>
#include "Tank.h"

Tank::Tank(GameState* gameState) {
    this->gameState=gameState;
    this->xPos=100;
    this->yPos=100;
    this->width=gameState->defaultTankWidth;
    this->height=gameState->defaultTankHeight;
    this->rotation=0;
}

Point Tank::getTopLeftCorner() {
    struct Point point {
            this->xPos - this->width/2, this->yPos - this->height/2
    };
    return this->rotatePoint(point);
}
Point Tank::getTopRightCorner() {
    struct Point point {
            this->xPos + this->width/2, this->yPos - this->height/2
    };
    return this->rotatePoint(point);
}
Point Tank::getBottomLeftCorner() {
    struct Point point {
            this->xPos - this->width/2, this->yPos + this->height/2
    };
    return this->rotatePoint(point);
}
Point Tank::getBottomRightCorner() {
    struct Point point {
            this->xPos + this->width/2, this->yPos + this->height/2
    };
    return this->rotatePoint(point);
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

void Tank::move(float distance) {
    float rotationRadians = this->rotation * M_PI / 180;
    this->xPos += distance * std::sin(rotationRadians);
    this->yPos -= distance * std::cos(rotationRadians);
}

bool Tank::isColliding() {
    return gameState->isWall(this->getTopLeftCorner()) ||
           gameState->isWall(this->getTopRightCorner()) ||
           gameState->isWall(this->getBottomLeftCorner()) ||
           gameState->isWall(this->getBottomRightCorner());
}

void Tank::moveIfPossible(float distance) {
    this->move(distance);
    if (this->isColliding()) {
        this->move(-distance);
    }
}

void Tank::rotate(float degrees) {
    this->setRotation(this->rotation + degrees);
}

float Tank::getXPos() {
    return xPos;
}
float Tank::getYPos() {
    return yPos;
}
float Tank::getWidth() {
    return width;
}
float Tank::getHeight() {
    return height;
}
float Tank::getRotation() {
    return rotation;
}

void Tank::setXPos(float xPos) {
    this->xPos = xPos;
}
void Tank::setYPos(float yPos) {
    this->yPos = yPos;
}
void Tank::setWidth(float width) {
    this->width = width;
}
void Tank::setHeight(float height) {
    this->height = height;
}
void Tank::setRotation(float rotation) {
    if (rotation < 0) {
        rotation += 360;
    }
    if (rotation >= 360) {
        rotation -= 360;
    }
    this->rotation = rotation;
}
