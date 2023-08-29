#include "IO.h"

IO::IO(GameState &gameState): gameState(gameState) {
    this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tank Game");
}
IO::~IO() {
    delete window;
}

sf::RenderWindow &IO::getWindow() {
    return *window;
}

bool IO::rightArrowPressed() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
}

bool IO::leftArrowPressed() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
}

bool IO::upArrowPressed() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
}

bool IO::downArrowPressed() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
}

bool IO::gameIsRunning() {
    return window->isOpen();
}

void IO::processEvents() {
    // close window if needed
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
    }
}

void IO::clear() {
    window->clear(sf::Color::White);
}

void IO::drawTanks() {
    sf::RectangleShape tank;
    tank.setFillColor(sf::Color::Black);
    tank.setOrigin(TANK_WIDTH/2, TANK_HEIGHT/2);
    tank.setPosition(gameState.tanks.front()->getXPos(), gameState.tanks.front()->getYPos());
    tank.setRotation(gameState.tanks.front()->getRotation());

    tank.setSize(sf::Vector2f(TANK_WIDTH, TANK_HEIGHT));
    window->draw(tank);
}

void IO::drawWalls() {
    sf::RectangleShape wall;
    wall.setFillColor(sf::Color::Black);

    wall.setSize(sf::Vector2f(WALL_LENGTH, WALL_THICKNESS));
    int horizontalWallsRows = sizeof(gameState.horizontalWalls) / sizeof(gameState.horizontalWalls[0]);
    int horizontalWallsColumns = sizeof(gameState.horizontalWalls[0]) / sizeof(gameState.horizontalWalls[0][0]);
    for (int y = 0; y < horizontalWallsRows; y++) {
        for (int x = 0; x < horizontalWallsColumns; x++) {
            if (gameState.horizontalWalls[y][x] == 1) {
                wall.setPosition(x*WALL_LENGTH, y*WALL_LENGTH);
                window->draw(wall);
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
                window->draw(wall);
            }
        }
    }
}

void IO::display() {
    window->display();
}
