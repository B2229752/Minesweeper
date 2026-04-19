#include "Cell.h"

Cell::Cell() : isMine(false), isRevealed(false), isFlagged(false), adjacentMines(0) {}

bool Cell::getIsMine() const { return isMine; }
void Cell::setMine() { isMine = true; }
bool Cell::getIsRevealed() const { return isRevealed; }
void Cell::reveal() { isRevealed = true; }
bool Cell::getIsFlagged() const { return isFlagged; }
void Cell::toggleFlag() { isFlagged = !isFlagged; }
void Cell::setAdjacentMines(int count) { adjacentMines = count; }
int Cell::getAdjacentMines() const { return adjacentMines; }