#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <queue>
#include "Cell.h"
using namespace std;

class Board {
private:
    int rows, cols, totalMines;
    vector<vector<Cell>> grid;
    bool firstMoveDone;
    int flagsLeft;
    bool isValid(int x, int y) const;
    void calculateNearbyMines();
    void revealRecursive(int x, int y);

public:
    Board(int r, int c, int m);
    bool revealCell(int x, int y);
    void toggleFlag(int x, int y);
    int getFlagsLeft() const;
    bool checkWin() const;
    void print(bool revealAll = false, int explodedX = -1, int explodedY = -1) const;
};

#endif
