#include "Game.h"
#include <iostream>
using namespace std;

Game::Game(int r, int c, int m) : board(r, c, m), gameOver(false), explodedX(-1), explodedY(-1) {}

void Game::start() {
    while (!gameOver) {
        cout << "Flags left: " << board.getFlagsLeft() << endl;
        board.print(false, explodedX, explodedY);
        cout << "Input operation (R x y = Reveal, F x y = Flag): ";
        char cmd;
        int x, y;
        cin >> cmd >> x >> y;

        if (cmd == 'R' || cmd == 'r') {
            if (board.revealCell(x, y)) {
                explodedX = x;
                explodedY = y;
                board.print(true, explodedX, explodedY);
                cout << "Game over." << endl;
                gameOver = true;
            } else if (board.checkWin()) {
                board.print(true);
                cout << "you won!" << endl;
                gameOver = true;
            }
        } else if (cmd == 'F' || cmd == 'f') {
            board.toggleFlag(x, y);
        }
    }
}
