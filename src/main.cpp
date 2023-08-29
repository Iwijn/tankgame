#include <cmath>
#include <iostream>
#include "GameState.h"
#include "debug.h"
#include "IO.h"
#include "util.h"

int main() {
    // initialize game
    GameState gameState(WALL_LENGTH, WALL_THICKNESS, TANK_WIDTH, TANK_HEIGHT);
    Tank tank(gameState);
    gameState.tanks.push_back(&tank);

    // make IO object
    IO io(gameState);

    // initialize debug singleton
    if (DEBUG) Debug::GetInstance(&io);

    // game loop
    while (io.gameIsRunning())
    {
        io.processEvents();

        // 60 game ticks per seconds
        if (timeSinceEpochMillisec() - gameState.prevLoopTime > 1000/FPS) {
            gameState.prevLoopTime = timeSinceEpochMillisec();

            io.clear();

            if (io.rightArrowPressed()) {
                gameState.tanks.front()->rotateIfPossible(TANK_TURN_SPEED);
            }
            if (io.leftArrowPressed()) {
                gameState.tanks.front()->rotateIfPossible(-TANK_TURN_SPEED);
            }
            if (io.upArrowPressed()) {
                gameState.tanks.front()->moveIfPossible(TANK_MOVE_SPEED);
            }
            if (io.downArrowPressed()) {
                gameState.tanks.front()->moveIfPossible(-TANK_MOVE_SPEED);
            }

            io.drawWalls();
            io.drawTanks();

            if (DEBUG) Debug::GetInstance()->draw(gameState);

            // Update the window
            io.display();
        }
    }
    return EXIT_SUCCESS;
}
