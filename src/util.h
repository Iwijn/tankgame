#pragma once
#include <chrono>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS 60
#define TANK_MOVE_SPEED 2.5
#define TANK_TURN_SPEED 4
#define TANK_WIDTH 25
#define TANK_HEIGHT 40
#define WALL_THICKNESS 7
#define WALL_LENGTH 60
#define DEBUG false
#define COLLISION_TESTING false

enum Direction {NORTH, EAST, SOUTH, WEST};
Direction operator++(Direction& direction);
Direction operator--(Direction& direction);
bool directionIsHorizontal(Direction direction);

struct Point {
    float x;
    float y;
};

struct GridPoint {
    int x;
    int y;
};
GridPoint operator+(GridPoint a, GridPoint b);

uint64_t timeSinceEpochMillisec();
Point rotatePoint(Point point, Point pivotPoint, float angleInDegrees);
