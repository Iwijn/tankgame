#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameState.h"

void drawTank(sf::RenderWindow &window, GameState *gameState);

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(400, 300), "Tank Game");

    auto gameState = new GameState();

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
                gameState->xPos += 10;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                gameState->xPos -= 10;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                gameState->yPos -= 10;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                gameState->yPos += 10;
            }

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
    tank.setPosition(gameState->xPos, gameState->yPos);

    tank.setSize(sf::Vector2f(50, 50));
    window.draw(tank);

}