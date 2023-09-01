#include <cmath>
#include "util.h"

Direction operator++(Direction& direction) {
    direction = static_cast<Direction>((direction + 1) % (WEST + 1));
    return direction;
}

Direction operator--(Direction& direction) {
    direction = static_cast<Direction>((direction - 1 + (WEST + 1)) % (WEST + 1));
    return direction;
}

bool directionIsHorizontal(Direction direction) {
    return direction == EAST || direction == WEST;
}

GridPoint operator+(GridPoint a, GridPoint b) {
    return GridPoint {a.x + b.x, a.y + b.y};
}

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

