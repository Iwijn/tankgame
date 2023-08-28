#ifndef TANKGAME_DEBUG_H
#define TANKGAME_DEBUG_H

#define CORNER_MARKER_RADIUS 2
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WALL_THICKNESS 10
#define WALL_LENGTH 50
#define COLLISION_TESTING false

#include <SFML/Graphics.hpp>
#include "GameState.h"

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

    void draw(GameState &gameState);
    void drawCornerPointsOfTanks(GameState &gameState);
    void drawGrid();
    void testWallCollision(GameState &gameState);
};

Debug *Debug::singleton_ = nullptr;
Debug *Debug::GetInstance(const sf::RenderWindow *window)
{
    if(singleton_ == nullptr){
        singleton_ = new Debug(window);
    }
    return singleton_;
}

void Debug::draw(GameState &gameState) {
    drawCornerPointsOfTanks(gameState);
    drawGrid();
    if (COLLISION_TESTING) {
        testWallCollision(gameState);
    }
}

void Debug::drawCornerPointsOfTanks(GameState &gameState) {
    sf::CircleShape point;
    point.setRadius(CORNER_MARKER_RADIUS);
    point.setFillColor(sf::Color::Red);
    point.setOrigin(CORNER_MARKER_RADIUS, CORNER_MARKER_RADIUS);
    for (auto tank : gameState.tanks) {
        // draw corner points
        point.setPosition(tank->getTopLeftCorner().x, tank->getTopLeftCorner().y);
        window->draw(point);
        point.setPosition(tank->getTopRightCorner().x, tank->getTopRightCorner().y);
        window->draw(point);
        point.setPosition(tank->getBottomLeftCorner().x, tank->getBottomLeftCorner().y);
        window->draw(point);
        point.setPosition(tank->getBottomRightCorner().x, tank->getBottomRightCorner().y);
        window->draw(point);
    }

}

void Debug::drawGrid() {
    sf::Vertex line[2];
    line[0].color = sf::Color::Blue;
    line[1].color = sf::Color::Blue;
    for (int i = 0; i < WINDOW_WIDTH/WALL_LENGTH; i++) {
        line[0].position = sf::Vector2f(i*WALL_LENGTH, 0);
        line[1].position = sf::Vector2f(i*WALL_LENGTH, WINDOW_HEIGHT);
        window->draw(line, 2, sf::Lines);
    }

    for (int i = 0; i < WINDOW_HEIGHT/WALL_LENGTH; i++) {
        line[0].position = sf::Vector2f(0, i*WALL_LENGTH);
        line[1].position = sf::Vector2f(WINDOW_WIDTH, i*WALL_LENGTH);
        window->draw(line, 2, sf::Lines);
    }
}

void Debug::testWallCollision(GameState &gameState) {

    for (int i = 0; i < 1000; i++) {
        auto x = (float) (random() % WINDOW_WIDTH);
        auto y = (float) (random() % WINDOW_HEIGHT);
        sf::CircleShape point;
        point.setRadius(1);
        if (gameState.isWall(Point {x, y})) {
            point.setFillColor(sf::Color::Red);
        } else {
            point.setFillColor(sf::Color::Green);
        }
        point.setOrigin(1, 1);
        point.setPosition(x, y);
        window->draw(point);
    }
}

#endif //TANKGAME_DEBUG_H
