#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameState.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS 60
#define TANK_MOVE_SPEED 3
#define TANK_TURN_SPEED 3
#define TANK_WIDTH 30
#define TANK_HEIGHT 50
#define WALL_THICKNESS 10
#define WALL_LENGTH 50
#define CORNER_MARKER_RADIUS 2
#define DEBUG false

void drawTank(sf::RenderWindow &window, GameState *gameState);
void drawWalls(sf::RenderWindow &window, GameState *gameState);
void moveLeftIfPossible(GameState *gameState);
void moveForwardIfPossible(GameState *gameState);
void moveBackwardsIfPossible(GameState *gameState);
void turnLeftIfPossible(GameState *gameState);
void turnRightIfPossible(GameState *gameState);
void drawGrid(sf::RenderWindow &window);
void testWallCollision(sf::RenderWindow &window, GameState *gameState);


int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tank Game");

    auto gameState = new GameState(WALL_LENGTH, WALL_THICKNESS);
    auto tank = Tank(TANK_WIDTH, TANK_HEIGHT);
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
            if (DEBUG) {
                drawGrid(window);
                testWallCollision(window, gameState);
            }
            // Update the window
            window.display();
        }
    }

    return EXIT_SUCCESS;
}

void moveForwardIfPossible(GameState *gameState) {
    Tank *tank = &gameState->tanks.front();
    float rotationRadians = gameState->tanks.front().rotation * (M_PI / 180);
    float newXPos = tank->xPos + ((float) TANK_MOVE_SPEED) * std::sin(rotationRadians);
    float newYPos = tank->yPos - ((float) TANK_MOVE_SPEED) * std::cos(rotationRadians);
    Tank *movedTank = new Tank(TANK_WIDTH, TANK_HEIGHT);
    movedTank->xPos = newXPos;
    movedTank->yPos = newYPos;
    movedTank->rotation = tank->rotation;
    if (!gameState->isWall(movedTank->getTopLeftCorner()) &&
    !gameState->isWall(movedTank->getTopRightCorner()) &&
    !gameState->isWall(movedTank->getBottomLeftCorner()) &&
    !gameState->isWall(movedTank->getBottomRightCorner())) {
        tank->xPos = newXPos;
        tank->yPos = newYPos;
    }
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

void drawTank(sf::RenderWindow &window, GameState *gameState) {
    sf::RectangleShape tank;
    tank.setFillColor(sf::Color::Black);
    tank.setOrigin(TANK_WIDTH/2, TANK_HEIGHT/2);
    tank.setPosition(gameState->tanks.front().xPos, gameState->tanks.front().yPos);
    tank.setRotation(gameState->tanks.front().rotation);

    tank.setSize(sf::Vector2f(TANK_WIDTH, TANK_HEIGHT));
    window.draw(tank);

    if (DEBUG) {
        // draw corner points
        sf::CircleShape point;
        point.setRadius(CORNER_MARKER_RADIUS);
        point.setFillColor(sf::Color::Red);
        point.setOrigin(CORNER_MARKER_RADIUS, CORNER_MARKER_RADIUS);
        point.setPosition(gameState->tanks.front().getTopLeftCorner().x, gameState->tanks.front().getTopLeftCorner().y);
        window.draw(point);
        point.setPosition(gameState->tanks.front().getTopRightCorner().x, gameState->tanks.front().getTopRightCorner().y);
        window.draw(point);
        point.setPosition(gameState->tanks.front().getBottomLeftCorner().x, gameState->tanks.front().getBottomLeftCorner().y);
        window.draw(point);
        point.setPosition(gameState->tanks.front().getBottomRightCorner().x, gameState->tanks.front().getBottomRightCorner().y);
        window.draw(point);
    }
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

void drawGrid(sf::RenderWindow &window) {
    sf::Vertex line[2];
    line[0].color = sf::Color::Blue;
    line[1].color = sf::Color::Blue;
    for (int i = 0; i < WINDOW_WIDTH/WALL_LENGTH; i++) {
        line[0].position = sf::Vector2f(i*WALL_LENGTH, 0);
        line[1].position = sf::Vector2f(i*WALL_LENGTH, WINDOW_HEIGHT);
        window.draw(line, 2, sf::Lines);
    }

    for (int i = 0; i < WINDOW_HEIGHT/WALL_LENGTH; i++) {
        line[0].position = sf::Vector2f(0, i*WALL_LENGTH);
        line[1].position = sf::Vector2f(WINDOW_WIDTH, i*WALL_LENGTH);
        window.draw(line, 2, sf::Lines);
    }
}

void testWallCollision(sf::RenderWindow &window, GameState *gameState) {

    for (int i = 0; i < 1000; i++) {
        auto x = (float) (random() % WINDOW_WIDTH);
        auto y = (float) (random() % WINDOW_HEIGHT);
        sf::CircleShape point;
        point.setRadius(1);
        if (gameState->isWall(Point {x, y})) {
            point.setFillColor(sf::Color::Red);
        } else {
            point.setFillColor(sf::Color::Green);
        }
        point.setOrigin(1, 1);
        point.setPosition(x, y);
        window.draw(point);
    }
}
