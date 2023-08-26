#ifndef TANKGAME_DEBUG_H
#define TANKGAME_DEBUG_H

#define CORNER_MARKER_RADIUS 2
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WALL_THICKNESS 10
#define WALL_LENGTH 50


#include <SFML/Graphics.hpp>
#include "GameState.h"


void drawCornerPointsOfTanks(sf::RenderWindow &window, GameState &gameState);
void drawGrid(sf::RenderWindow &window);
void testWallCollision(sf::RenderWindow &window, GameState &gameState);

#endif //TANKGAME_DEBUG_H
