#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.h"

class IO {
private:
    sf::RenderWindow &window;
    GameState &gameState;
public:
    IO(sf::RenderWindow &window, GameState &gameState);
    bool rightArrowPressed();
    bool leftArrowPressed();
    bool upArrowPressed();
    bool downArrowPressed();
    bool gameIsRunning();
    void processEvents();
    void clear();
    void drawTanks();
    void drawWalls();
    void display();
};
