#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameState.h"

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 300
#define FPS 60
#define TANK_STEP 10
#define TANK_WIDTH 50
#define TANK_HEIGHT 50
#define WALL_THICKNESS 10
#define WALL_LENGTH 50

void drawTank(sf::RenderWindow &window, GameState *gameState);
void drawWalls(sf::RenderWindow &window, GameState *gameState);

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tank Game");

    auto gameState = new GameState();
    auto tank = Tank();
    gameState->tanks.push_back(tank);
    // Start the game loop
    while (window.isOpen())
    {
        //  Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // 60 game ticks per seconds
        if (timeSinceEpochMillisec() - gameState->prevLoopTime > 1000/FPS) {
            gameState->prevLoopTime = timeSinceEpochMillisec();
            // Clear screen
            window.clear(sf::Color::White);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                gameState->tanks.front().xPos += TANK_STEP;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                gameState->tanks.front().xPos -= TANK_STEP;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                gameState->tanks.front().yPos -= TANK_STEP;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                gameState->tanks.front().yPos += TANK_STEP;
            }

            drawWalls(window, gameState);
            drawTank(window, gameState);

            // Update the window
            window.display();
        }
    }

    return EXIT_SUCCESS;
}

void drawTank(sf::RenderWindow &window, GameState *gameState) {
    sf::RectangleShape tank;
    tank.setFillColor(sf::Color::Black);
    tank.setPosition(gameState->tanks.front().xPos, gameState->tanks.front().yPos);

    tank.setSize(sf::Vector2f(TANK_WIDTH, TANK_HEIGHT));
    window.draw(tank);
}

void drawWalls(sf::RenderWindow &window, GameState *gameState) {
    sf::RectangleShape wall;
    wall.setFillColor(sf::Color::Black);

    wall.setSize(sf::Vector2f(WALL_LENGTH, WALL_THICKNESS));
    int horizontalWallsRows = sizeof(gameState->horizontalWalls10) / sizeof(gameState->horizontalWalls10[0]);
    int horizontalWallsColumns = sizeof(gameState->horizontalWalls10[0]) / sizeof(gameState->horizontalWalls10[0][0]);
    for (int y = 0; y < horizontalWallsRows; y++) {
        for (int x = 0; x < horizontalWallsColumns; x++) {
            if (gameState->horizontalWalls10[y][x] == 1) {
                wall.setPosition(x*WALL_LENGTH, y*WALL_LENGTH);
                window.draw(wall);
            }
        }
    }

    int verticalWallsRows = sizeof(gameState->verticalWalls10) / sizeof(gameState->verticalWalls10[0]);
    int verticalWallsColumns = sizeof(gameState->verticalWalls10[0]) / sizeof(gameState->verticalWalls10[0][0]);
    wall.setSize(sf::Vector2f(WALL_THICKNESS, WALL_LENGTH));
    for (int y = 0; y < verticalWallsRows; y++) {
        for (int x = 0; x < verticalWallsColumns; x++) {
            if (gameState->verticalWalls10[y][x] == 1) {
                wall.setPosition(x*WALL_LENGTH, y*WALL_LENGTH);
                window.draw(wall);
            }
        }
    }
}
