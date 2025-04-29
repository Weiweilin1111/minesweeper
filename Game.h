#ifndef GAME_H
#define GAME_H

#include "Board.h"

class Game {
private:
    Board board;
    bool gameOver;
    int explodedX, explodedY;

public:
    Game(int r, int c, int m);
    void start();
};

#endif