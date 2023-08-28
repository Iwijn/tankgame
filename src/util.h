#pragma once
#include <chrono>

#define DEBUG false

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
