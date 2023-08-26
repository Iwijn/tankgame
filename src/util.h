#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <chrono>

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

#endif

