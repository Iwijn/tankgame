#pragma once
#include <chrono>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS 60
#define TANK_MOVE_SPEED 3
#define TANK_TURN_SPEED 3
#define TANK_WIDTH 30
#define TANK_HEIGHT 50
#define WALL_THICKNESS 10
#define WALL_LENGTH 50
#define DEBUG false
#define COLLISION_TESTING false

struct Point {
    float x;
    float y;
};
struct GridPoint {
    int x;
    int y;
};
uint64_t timeSinceEpochMillisec();
Point rotatePoint(Point point, Point pivotPoint, float angleInDegrees);
