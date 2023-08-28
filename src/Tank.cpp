#include <iostream>
#include "Tank.h"


Tank::Tank(GameState &gameState) : gameState(gameState) {
    this->xPos=100;
    this->yPos=100;
    this->width=gameState.defaultTankWidth;
    this->height=gameState.defaultTankHeight;
    this->rotation=0;
}

Point Tank::getMiddlePoint() {
    return Point {this->xPos, this->yPos};
}

Point Tank::getTopLeftCorner() {
    struct Point point {
            this->xPos - this->width/2, this->yPos - this->height/2
    };
    return rotatePoint(point, getMiddlePoint(), this->rotation);
}
Point Tank::getTopRightCorner() {
    struct Point point {
            this->xPos + this->width/2, this->yPos - this->height/2
    };
    return rotatePoint(point, getMiddlePoint(), this->rotation);
}
Point Tank::getBottomLeftCorner() {
    struct Point point {
            this->xPos - this->width/2, this->yPos + this->height/2
    };
    return rotatePoint(point, getMiddlePoint(), this->rotation);
}
Point Tank::getBottomRightCorner() {
    struct Point point {
            this->xPos + this->width/2, this->yPos + this->height/2
    };
    return rotatePoint(point, getMiddlePoint(), this->rotation);
}

void Tank::moveIfPossible(float distance) {
    this->move(distance);
    if (this->isColliding()) {
        this->move(-distance);
    }
}

void Tank::move(float distance) {
    float rotationRadians = this->rotation * M_PI / 180;
    this->xPos += distance * std::sin(rotationRadians);
    this->yPos -= distance * std::cos(rotationRadians);
}

void Tank::rotateIfPossible(float degrees) {
    this->rotate(degrees);
    if (this->isColliding()) {
        this->rotate(-degrees);
    }
}

void Tank::rotate(float degrees) {
    this->setRotation(this->rotation + degrees);
}


bool Tank::isColliding() {
    // check if tank corners are colliding with any walls
    if (gameState.isWall(this->getTopLeftCorner()) ||
        gameState.isWall(this->getTopRightCorner()) ||
        gameState.isWall(this->getBottomLeftCorner()) ||
        gameState.isWall(this->getBottomRightCorner()) ) {
        return true;
    }

    // check if wall corners of neighboring grid squares are colliding with tank
    std::list<GridPoint> neighboringGridSquares;
    // get 3x3 grid of grid squares around tank (less if tank at edge)
    this->getCollisionZoneGridPoints(neighboringGridSquares);
    for (auto gridPoint : neighboringGridSquares) {
        std::list<Point> cornerPoints;
        // get corners of walls in grid square
        gameState.getCornerPointsOfWalls(cornerPoints, gridPoint);
        // if any of the corners are inside the tank, then there is a collision
        for (auto cornerPoint : cornerPoints) {
            if (this->isTank(cornerPoint)) {
                return true;
            }
        }
    }

    return false;
}

bool Tank::isTank(Point point) {
    // rotate tank to 0 degrees
    float savedRotation = this->rotation;
    this->rotate(-savedRotation);

    // rotate point in the same way
    Point rotatedPoint = rotatePoint(point, getMiddlePoint(), -savedRotation);

    // do easy collision check because tank is rotated 0 degrees
    if (this->getTopLeftCorner().x <= rotatedPoint.x && rotatedPoint.x < this->getTopRightCorner().x &&
        this->getTopLeftCorner().y <= rotatedPoint.y && rotatedPoint.y < this->getBottomLeftCorner().y ) {
        // rotate tank back
        this->rotate(savedRotation);
        return true;
    }
    this->rotate(savedRotation);
    return false;
}

void Tank::getCollisionZoneGridPoints(std::list<GridPoint> &neighboringGridSquares) {
    GridPoint middleGridSquare = gameState.getGridPoint(Point {this->xPos, this->yPos});
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <=1; x++) {
            auto neighboringGridSquare = GridPoint {middleGridSquare.x + x, middleGridSquare.y + y};
            if (neighboringGridSquare.x >= 0 && neighboringGridSquare.y >= 0) {
                neighboringGridSquares.push_back(neighboringGridSquare);
            }
        }
    }
    if (DEBUG) Debug::GetInstance()->drawCollisionZone(neighboringGridSquares);
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
