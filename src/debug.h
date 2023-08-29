#pragma once

#define CORNER_MARKER_RADIUS 2
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WALL_THICKNESS 10
#define WALL_LENGTH 50
#define WALL_LENGTH 50
#define COLLISION_TESTING false

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "util.h"
#include "IO.h"

class GameState;
class Tank;
class IO;
class Debug {
protected:
    Debug(const IO *io)
    {
        this->io = const_cast<IO *>(io);
    }

    static Debug* singleton_;

    std::string value_;
    IO *io;

public:
    static Debug *GetInstance(const IO *io);
    static Debug *GetInstance();

    void draw(GameState &gameState);
    void drawCornerPointsOfTanks(GameState &gameState);
    void drawGrid();
    void testWallCollision(GameState &gameState);
    void drawCollisionZone(std::list<GridPoint> & neighboringGridPoints);
    void drawWallCornerPoints(std::list<Point>& cornerPoints);
};
