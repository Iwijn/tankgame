#pragma once

#define CORNER_MARKER_RADIUS 2
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WALL_THICKNESS 10
#define WALL_LENGTH 50
#define COLLISION_TESTING false

#include <SFML/Graphics.hpp>
#include "GameState.h"

class GameState;
class Tank;
class Debug {
protected:
    Debug(const sf::RenderWindow *window)
    {
        this->window = const_cast<sf::RenderWindow *>(window);
    }

    static Debug* singleton_;

    std::string value_;
    sf::RenderWindow *window;

public:
    static Debug *GetInstance(const sf::RenderWindow *window);
    static Debug *GetInstance();

    void draw(GameState &gameState);
    void drawCornerPointsOfTanks(GameState &gameState);
    void drawGrid();
    void testWallCollision(GameState &gameState);
};
