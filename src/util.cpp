#include <cmath>
#include "util.h"

uint64_t timeSinceEpochMillisec() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

Point rotatePoint(Point point, Point pivotPoint, float angleInDegrees)
{
    float angle = angleInDegrees * (float) (M_PI / 180);
    float s = std::sin(angle);
    float c = std::cos(angle);

    // translate point to origin:
    float originX = point.x - pivotPoint.x;
    float originY = point.y - pivotPoint.y;

    // rotate point, add origin coord back
    return Point {
            pivotPoint.x + (originX * c - originY * s), pivotPoint.y + (originX * s + originY * c)
    };
}