#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "debug.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS 60
#define TANK_MOVE_SPEED 3
#define TANK_TURN_SPEED 3
#define TANK_WIDTH 30
#define TANK_HEIGHT 50
#define WALL_THICKNESS 10
#define WALL_LENGTH 50

void drawTank(sf::RenderWindow &window, GameState &gameState);
void drawWalls(sf::RenderWindow &window, GameState &gameState);

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tank Game");
    // initialize debug singleton
    if (DEBUG) Debug::GetInstance(&window);
    GameState gameState(WALL_LENGTH, WALL_THICKNESS, TANK_WIDTH, TANK_HEIGHT);
    Tank tank(gameState);
    gameState.tanks.push_back(&tank);
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
        if (timeSinceEpochMillisec() - gameState.prevLoopTime > 1000/FPS) {
            gameState.prevLoopTime = timeSinceEpochMillisec();
            // Clear screen
            window.clear(sf::Color::White);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                gameState.tanks.front()->rotateIfPossible(TANK_TURN_SPEED);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                gameState.tanks.front()->rotateIfPossible(-TANK_TURN_SPEED);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                gameState.tanks.front()->moveIfPossible(TANK_MOVE_SPEED);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                gameState.tanks.front()->moveIfPossible(-TANK_MOVE_SPEED);
            }

            drawWalls(window, gameState);
            drawTank(window, gameState);
            if (DEBUG) Debug::GetInstance()->draw(gameState);

            // Update the window
            window.display();
        }
    }
    return EXIT_SUCCESS;
}

void drawTank(sf::RenderWindow &window, GameState &gameState) {
    sf::RectangleShape tank;
    tank.setFillColor(sf::Color::Black);
    tank.setOrigin(TANK_WIDTH/2, TANK_HEIGHT/2);
    tank.setPosition(gameState.tanks.front()->getXPos(), gameState.tanks.front()->getYPos());
    tank.setRotation(gameState.tanks.front()->getRotation());

    tank.setSize(sf::Vector2f(TANK_WIDTH, TANK_HEIGHT));
    window.draw(tank);

    if (DEBUG) {
        // draw corner points
        sf::CircleShape point;
        point.setRadius(CORNER_MARKER_RADIUS);
        point.setFillColor(sf::Color::Red);
        point.setOrigin(CORNER_MARKER_RADIUS, CORNER_MARKER_RADIUS);
        point.setPosition(gameState.tanks.front()->getTopLeftCorner().x, gameState.tanks.front()->getTopLeftCorner().y);
        window.draw(point);
        point.setPosition(gameState.tanks.front()->getTopRightCorner().x, gameState.tanks.front()->getTopRightCorner().y);
        window.draw(point);
        point.setPosition(gameState.tanks.front()->getBottomLeftCorner().x, gameState.tanks.front()->getBottomLeftCorner().y);
        window.draw(point);
        point.setPosition(gameState.tanks.front()->getBottomRightCorner().x, gameState.tanks.front()->getBottomRightCorner().y);
        window.draw(point);
    }
}

void drawWalls(sf::RenderWindow &window, GameState &gameState) {
    sf::RectangleShape wall;
    wall.setFillColor(sf::Color::Black);

    wall.setSize(sf::Vector2f(WALL_LENGTH, WALL_THICKNESS));
    int horizontalWallsRows = sizeof(gameState.horizontalWalls) / sizeof(gameState.horizontalWalls[0]);
    int horizontalWallsColumns = sizeof(gameState.horizontalWalls[0]) / sizeof(gameState.horizontalWalls[0][0]);
    for (int y = 0; y < horizontalWallsRows; y++) {
        for (int x = 0; x < horizontalWallsColumns; x++) {
            if (gameState.horizontalWalls[y][x] == 1) {
                wall.setPosition(x*WALL_LENGTH, y*WALL_LENGTH);
                window.draw(wall);
            }
        }
    }

    int verticalWallsRows = sizeof(gameState.verticalWalls) / sizeof(gameState.verticalWalls[0]);
    int verticalWallsColumns = sizeof(gameState.verticalWalls[0]) / sizeof(gameState.verticalWalls[0][0]);
    wall.setSize(sf::Vector2f(WALL_THICKNESS, WALL_LENGTH));
    for (int y = 0; y < verticalWallsRows; y++) {
        for (int x = 0; x < verticalWallsColumns; x++) {
            if (gameState.verticalWalls[y][x] == 1) {
                wall.setPosition(x*WALL_LENGTH, y*WALL_LENGTH);
                window.draw(wall);
            }
        }
    }
}