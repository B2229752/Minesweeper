#ifndef CELL_H
#define CELL_H

class Cell {
private:
    bool isMine;
    bool isRevealed;
    bool isFlagged;
    int adjacentMines;

public:
    Cell();
    bool getIsMine() const;
    void setMine();
    bool getIsRevealed() const;
    void reveal();
    bool getIsFlagged() const;
    void toggleFlag();
    void setAdjacentMines(int count);
    int getAdjacentMines() const;
};

#endif