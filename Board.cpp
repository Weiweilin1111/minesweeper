#include "Board.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Board::Board(int r, int c, int m) : rows(r), cols(c), totalMines(m), grid(r, vector<Cell>(c)), firstMoveDone(false), flagsLeft(m) {
    srand(time(0));
}

bool Board::isValid(int x, int y) const {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

void Board::calculateNearbyMines() {
    int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j].isMine()) continue;
            int count = 0;
            for (int d = 0; d < 8; ++d) {
                int ni = i + dx[d], nj = j + dy[d];
                if (isValid(ni, nj) && grid[ni][nj].isMine()) count++;
            }
            grid[i][j].setNearbyMines(count);
        }
    }
}

void Board::revealRecursive(int x, int y) {
    if (!isValid(x, y)) return;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    queue<pair<int, int>> q;
    q.push({x, y});
    visited[x][y] = true;

    while (!q.empty()) {
        auto p = q.front();
        int cx = p.first;
        int cy = p.second;
        q.pop();
        grid[cx][cy].reveal();

        if (grid[cx][cy].getNearbyMines() != 0) continue;

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int nx = cx + dx, ny = cy + dy;
                if (isValid(nx, ny) && !visited[nx][ny] && !grid[nx][ny].isRevealed() && !grid[nx][ny].isFlagged()) {
                    visited[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }
    }
}

bool Board::revealCell(int x, int y) {
    if (!isValid(x, y) || grid[x][y].isRevealed()) return false;

    if (!firstMoveDone) {
        vector<pair<int, int>> forbidden;
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int nx = x + dx, ny = y + dy;
                if (isValid(nx, ny)) forbidden.emplace_back(nx, ny);
            }
        }
        int placed = 0;
        while (placed < totalMines) {
            int rx = rand() % rows;
            int ry = rand() % cols;
            if (grid[rx][ry].isMine()) continue;
            bool isForbidden = false;
            for (auto& p : forbidden) if (p.first == rx && p.second == ry) { isForbidden = true; break; }
            if (isForbidden) continue;
            grid[rx][ry].placeMine();
            placed++;
        }
        calculateNearbyMines();
        firstMoveDone = true;
    }

    grid[x][y].reveal();
    if (grid[x][y].isMine()) return true;
    if (grid[x][y].getNearbyMines() == 0) revealRecursive(x, y);
    return false;
}

void Board::toggleFlag(int x, int y) {
    if (isValid(x, y) && !grid[x][y].isRevealed()) {
        if (grid[x][y].isFlagged()) flagsLeft++;
        else flagsLeft--;
        grid[x][y].toggleFlag();
    }
}

int Board::getFlagsLeft() const { return flagsLeft; }

bool Board::checkWin() const {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (!grid[i][j].isMine() && !grid[i][j].isRevealed()) return false;
    return true;
}

void Board::print(bool revealAll, int explodedX, int explodedY) const {
    cout << "   ";
    for (int j = 0; j < cols; ++j) cout << j << " ";
    cout << endl;
    for (int i = 0; i < rows; ++i) {
        cout << i << " |";
        for (int j = 0; j < cols; ++j) {
            const Cell& cell = grid[i][j];
            if (i == explodedX && j == explodedY) cout << "X";
            else if (revealAll || cell.isRevealed()) {
                if (cell.isMine()) cout << "*";
                else if (cell.getNearbyMines() > 0) cout << cell.getNearbyMines();
                else cout << " ";
            } else if (cell.isFlagged()) cout << "F";
            else cout << "#";
            cout << " ";
        }
        cout << "|" << endl;
    }
}