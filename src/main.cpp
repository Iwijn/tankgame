#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameState.h"

void drawTank(sf::RenderWindow &window, GameState *gameState);
void drawWalls(sf::RenderWindow &window, GameState *gameState);

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(400, 300), "Tank Game");

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
        if (timeSinceEpochMillisec() - gameState->prevLoopTime > 1000/60) {
            gameState->prevLoopTime = timeSinceEpochMillisec();
            // Clear screen
            window.clear(sf::Color::White);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                gameState->tanks.front().xPos += 10;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                gameState->tanks.front().xPos -= 10;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                gameState->tanks.front().yPos -= 10;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                gameState->tanks.front().yPos += 10;
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

    tank.setSize(sf::Vector2f(50, 50));
    window.draw(tank);
}

void drawWalls(sf::RenderWindow &window, GameState *gameState) {
    sf::RectangleShape wall;
    wall.setFillColor(sf::Color::Black);

    wall.setSize(sf::Vector2f(10, 50));
    int horizontalWallsRows = sizeof(gameState->horizontalWalls10) / sizeof(gameState->horizontalWalls10[0]);
    int horizontalWallsColumns = sizeof(gameState->horizontalWalls10[0]) / sizeof(gameState->horizontalWalls10[0][0]);
    for (int i = 0; i < horizontalWallsRows; i++) {
        for (int j = 0; j < horizontalWallsColumns; j++) {
            if (gameState->horizontalWalls10[i][j] == 1) {
                wall.setPosition(i*50, j*50);
                window.draw(wall);
            }
        }
    }

    int verticalWallsRows = sizeof(gameState->verticalWalls10) / sizeof(gameState->verticalWalls10[0]);
    int verticalWallsColumns = sizeof(gameState->verticalWalls10[0]) / sizeof(gameState->verticalWalls10[0][0]);
    wall.setSize(sf::Vector2f(50, 10));
    for (int i = 0; i < verticalWallsRows; i++) {
        for (int j = 0; j < verticalWallsColumns; j++) {
            if (gameState->verticalWalls10[i][j] == 1) {
                wall.setPosition(i*50, j*50);
                window.draw(wall);
            }
        }
    }
}
