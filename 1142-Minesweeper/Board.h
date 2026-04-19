#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Cell.h"

class Board {
private:
    int width;
    int height;
    int numMines;
    std::vector<std::vector<Cell>> grid;
    int hiddenSafeCells; // 用於判斷勝利條件

    void placeMines();
    void calculateAdjacentMines();

public:
    Board(int w = 10, int h = 10, int mines = 10);
    void display(bool revealAll = false);
    bool revealCell(int x, int y);
    void flagCell(int x, int y);
    bool checkWin() const;
    bool isValid(int x, int y) const;
};

#endif