#include "Board.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Board::Board(int w, int h, int mines) : width(w), height(h), numMines(mines) {
    grid.resize(height, std::vector<Cell>(width));
    hiddenSafeCells = width * height - numMines;
    placeMines();
    calculateAdjacentMines();
}

bool Board::isValid(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

void Board::placeMines() {
    srand(time(0));
    int minesPlaced = 0;
    while (minesPlaced < numMines) {
        int x = rand() % width;
        int y = rand() % height;
        if (!grid[y][x].getIsMine()) {
            grid[y][x].setMine();
            minesPlaced++;
        }
    }
}

void Board::calculateAdjacentMines() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (grid[y][x].getIsMine()) continue;
            int count = 0;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    int ny = y + dy;
                    int nx = x + dx;
                    if (isValid(nx, ny) && grid[ny][nx].getIsMine()) {
                        count++;
                    }
                }
            }
            grid[y][x].setAdjacentMines(count);
        }
    }
}

void Board::display(bool revealAll) {
    std::cout << "   ";
    for (int x = 0; x < width; ++x) std::cout << x << " ";
    std::cout << "\n";

    for (int y = 0; y < height; ++y) {
        std::cout << y << "  ";
        for (int x = 0; x < width; ++x) {
            Cell& c = grid[y][x];
            if (revealAll && c.getIsMine()) {
                std::cout << "* ";
            } else if (c.getIsRevealed()) {
                if (c.getIsMine()) std::cout << "* ";
                else if (c.getAdjacentMines() == 0) std::cout << "  ";
                else std::cout << c.getAdjacentMines() << " ";
            } else if (c.getIsFlagged()) {
                std::cout << "F ";
            } else {
                std::cout << "# ";
            }
        }
        std::cout << "\n";
    }
}

bool Board::revealCell(int x, int y) {
    if (!isValid(x, y) || grid[y][x].getIsRevealed() || grid[y][x].getIsFlagged()) {
        return false; // 安全：座標無效、已翻開或已插旗
    }

    grid[y][x].reveal();
    
    if (grid[y][x].getIsMine()) {
        return true; // 踩到地雷了
    }

    hiddenSafeCells--;

    // 如果是0，遞迴翻開周圍 (Flood-fill)
    if (grid[y][x].getAdjacentMines() == 0) {
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                if (dx != 0 || dy != 0) {
                    revealCell(x + dx, y + dy);
                }
            }
        }
    }
    return false;
}

void Board::flagCell(int x, int y) {
    if (isValid(x, y) && !grid[y][x].getIsRevealed()) {
        grid[y][x].toggleFlag();
    }
}

bool Board::checkWin() const {
    return hiddenSafeCells == 0;
}