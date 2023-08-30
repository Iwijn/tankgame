#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "util.h"
#include "IO.h"

class GameState;
class Tank;
class IO;
class Debug {
protected:
    Debug(IO *io)
    {
        this->io = io;
    }

    static Debug* singleton_;

    std::string value_;
    IO *io;

public:
    static Debug *GetInstance(IO *io);
    static Debug *GetInstance();

    void draw(GameState &gameState);
    void drawCornerPointsOfTanks(GameState &gameState);
    void drawGrid(GameState &gameState);
    void testWallCollision(GameState &gameState);
    void drawCollisionZone(std::list<GridPoint> & neighboringGridPoints);
    void drawWallCornerPoints(std::list<Point>& cornerPoints);
};
