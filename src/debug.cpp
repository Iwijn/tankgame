#include "debug.h"

void drawCornerPointsOfTanks(sf::RenderWindow &window, GameState &gameState) {
    sf::CircleShape point;
    point.setRadius(CORNER_MARKER_RADIUS);
    point.setFillColor(sf::Color::Red);
    point.setOrigin(CORNER_MARKER_RADIUS, CORNER_MARKER_RADIUS);
    for (auto tank : gameState.tanks) {
        // draw corner points
        point.setPosition(tank->getTopLeftCorner().x, tank->getTopLeftCorner().y);
        window.draw(point);
        point.setPosition(tank->getTopRightCorner().x, tank->getTopRightCorner().y);
        window.draw(point);
        point.setPosition(tank->getBottomLeftCorner().x, tank->getBottomLeftCorner().y);
        window.draw(point);
        point.setPosition(tank->getBottomRightCorner().x, tank->getBottomRightCorner().y);
        window.draw(point);
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

void testWallCollision(sf::RenderWindow &window, GameState &gameState) {

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
        window.draw(point);
    }
}
