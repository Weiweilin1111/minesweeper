#ifndef CELL_H
#define CELL_H

class Cell {
private:
    bool hasMine;
    bool revealed;
    bool flagged;
    int nearbyMines;

public:
    Cell();
    void placeMine();
    void reveal();
    void toggleFlag();
    bool isRevealed() const;
    bool isMine() const;
    bool isFlagged() const;
    int getNearbyMines() const;
    void setNearbyMines(int count);
};

#endif