#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameState.h"

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 300
#define FPS 60
#define TANK_MOVE_SPEED 6
#define TANK_TURN_SPEED 2
#define TANK_WIDTH 30
#define TANK_HEIGHT 50
#define WALL_THICKNESS 10
#define WALL_LENGTH 50

void drawTank(sf::RenderWindow &window, GameState *gameState);
void drawWalls(sf::RenderWindow &window, GameState *gameState);
void moveLeftIfPossible(GameState *gameState);
void moveForwardIfPossible(GameState *gameState);
void moveBackwardsIfPossible(GameState *gameState);
void turnLeftIfPossible(GameState *gameState);
void turnRightIfPossible(GameState *gameState);


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
                turnRightIfPossible(gameState);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                turnLeftIfPossible(gameState);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                moveForwardIfPossible(gameState);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                moveBackwardsIfPossible(gameState);
            }

            drawWalls(window, gameState);
            drawTank(window, gameState);

            // Update the window
            window.display();
        }
    }

    return EXIT_SUCCESS;
}

void moveForwardIfPossible(GameState *gameState) {
    float rotationRadians = gameState->tanks.front().rotation * M_PI / 180;
    gameState->tanks.front().xPos += ((float) TANK_MOVE_SPEED) * std::sin(rotationRadians);
    gameState->tanks.front().yPos -= ((float) TANK_MOVE_SPEED) * std::cos(rotationRadians);
}

void moveBackwardsIfPossible(GameState *gameState) {
    float rotationRadians = gameState->tanks.front().rotation * M_PI / 180;
    gameState->tanks.front().xPos -= ((float) TANK_MOVE_SPEED) * std::sin(rotationRadians);
    gameState->tanks.front().yPos += ((float) TANK_MOVE_SPEED) * std::cos(rotationRadians);
}

void turnLeftIfPossible(GameState *gameState) {
    gameState->tanks.front().rotation -= TANK_TURN_SPEED;
    if (gameState->tanks.front().rotation < 0) {
        gameState->tanks.front().rotation += 360;
    }
}

void turnRightIfPossible(GameState *gameState) {
    gameState->tanks.front().rotation += TANK_TURN_SPEED;
    if (gameState->tanks.front().rotation >= 360) {
        gameState->tanks.front().rotation -= 360;
    }
}

void moveLeftIfPossible(GameState *gameState) {
    if (!gameState->isWall(gameState->tanks.front().xPos - TANK_MOVE_SPEED, gameState->tanks.front().yPos)) {
        gameState->tanks.front().xPos -= TANK_MOVE_SPEED;
    }
}

void drawTank(sf::RenderWindow &window, GameState *gameState) {
    sf::RectangleShape tank;
    tank.setFillColor(sf::Color::Black);
    tank.setOrigin(TANK_WIDTH/2, TANK_HEIGHT/2);
    tank.setPosition(gameState->tanks.front().xPos, gameState->tanks.front().yPos);
    tank.setRotation(gameState->tanks.front().rotation);

    tank.setSize(sf::Vector2f(TANK_WIDTH, TANK_HEIGHT));
    window.draw(tank);
}

void drawWalls(sf::RenderWindow &window, GameState *gameState) {
    sf::RectangleShape wall;
    wall.setFillColor(sf::Color::Black);

    wall.setSize(sf::Vector2f(WALL_LENGTH, WALL_THICKNESS));
    int horizontalWallsRows = sizeof(gameState->horizontalWalls) / sizeof(gameState->horizontalWalls[0]);
    int horizontalWallsColumns = sizeof(gameState->horizontalWalls[0]) / sizeof(gameState->horizontalWalls[0][0]);
    for (int y = 0; y < horizontalWallsRows; y++) {
        for (int x = 0; x < horizontalWallsColumns; x++) {
            if (gameState->horizontalWalls[y][x] == 1) {
                wall.setPosition(x*WALL_LENGTH, y*WALL_LENGTH);
                window.draw(wall);
            }
        }
    }

    int verticalWallsRows = sizeof(gameState->verticalWalls) / sizeof(gameState->verticalWalls[0]);
    int verticalWallsColumns = sizeof(gameState->verticalWalls[0]) / sizeof(gameState->verticalWalls[0][0]);
    wall.setSize(sf::Vector2f(WALL_THICKNESS, WALL_LENGTH));
    for (int y = 0; y < verticalWallsRows; y++) {
        for (int x = 0; x < verticalWallsColumns; x++) {
            if (gameState->verticalWalls[y][x] == 1) {
                wall.setPosition(x*WALL_LENGTH, y*WALL_LENGTH);
                window.draw(wall);
            }
        }
    }
}
