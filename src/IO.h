#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.h"

class GameState;
class IO {
private:
    sf::RenderWindow *window;
    GameState &gameState;
public:
    explicit IO(GameState &gameState);
    ~IO();
    // should only be used publicly for debug purposes.
    sf::RenderWindow &getWindow();

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
