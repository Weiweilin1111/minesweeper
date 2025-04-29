#include "Cell.h"

Cell::Cell() : hasMine(false), revealed(false), flagged(false), nearbyMines(0) {}
void Cell::placeMine() { hasMine = true; }
void Cell::reveal() { revealed = true; }
void Cell::toggleFlag() { if (!revealed) flagged = !flagged; }
bool Cell::isRevealed() const { return revealed; }
bool Cell::isMine() const { return hasMine; }
bool Cell::isFlagged() const { return flagged; }
int Cell::getNearbyMines() const { return nearbyMines; }
void Cell::setNearbyMines(int count) { nearbyMines = count; }
