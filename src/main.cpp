#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "GameState.h"

void drawTank(sf::RenderWindow &window, GameState gameState);
uint64_t timeSinceEpochMillisec();

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(400, 300), "Tank Game");

    GameState gameState;
    gameState.xPos = 10;
    gameState.yPos = 10;
    gameState.prevLoopTime = timeSinceEpochMillisec();

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
        if (timeSinceEpochMillisec() - gameState.prevLoopTime > 1000/60) {
            gameState.prevLoopTime = timeSinceEpochMillisec();
            // Clear screen
            window.clear(sf::Color::White);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                gameState.xPos += 10;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                gameState.xPos -= 10;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                gameState.yPos -= 10;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                gameState.yPos += 10;
            }

            drawTank(window, gameState);

            // Update the window
            window.display();
        }
    }

    return EXIT_SUCCESS;
}

uint64_t timeSinceEpochMillisec() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void drawTank(sf::RenderWindow &window, GameState gameState) {
    sf::RectangleShape tank;
    tank.setFillColor(sf::Color::Black);
    tank.setPosition(gameState.xPos, gameState.yPos);

    tank.setSize(sf::Vector2f(50, 50));
    window.draw(tank);

}
