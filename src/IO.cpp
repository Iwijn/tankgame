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
    sf::RectangleShape rectangle;
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setOrigin(TANK_WIDTH/2, TANK_HEIGHT/2);
    rectangle.setSize(sf::Vector2f(TANK_WIDTH, TANK_HEIGHT));
    for (auto tank : gameState.tanks) {
        rectangle.setPosition(tank->getXPos(), tank->getYPos());
        rectangle.setRotation(tank->getRotation());
    }

    window->draw(rectangle);
}

void IO::drawWalls() {
    sf::RectangleShape wall;
    wall.setFillColor(sf::Color::Black);

    wall.setSize(sf::Vector2f(WALL_LENGTH, WALL_THICKNESS));
    for (int y = 0; y < gameState.map.height; y++) {
        for (int x = 0; x < gameState.map.width; x++) {
            if (gameState.map.isHWall(GridPoint {x, y})) {
                wall.setPosition(x*WALL_LENGTH, y*WALL_LENGTH);
                window->draw(wall);
            }
        }
    }

    wall.setSize(sf::Vector2f(WALL_THICKNESS, WALL_LENGTH));
    for (int y = 0; y < gameState.map.height; y++) {
        for (int x = 0; x < gameState.map.width; x++) {
            if (gameState.map.isVWall(GridPoint {x, y})) {
                wall.setPosition(x*WALL_LENGTH, y*WALL_LENGTH);
                window->draw(wall);
            }
        }
    }
}

void IO::display() {
    window->display();
}
