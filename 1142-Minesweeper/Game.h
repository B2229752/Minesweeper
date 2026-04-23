#ifndef GAME_H
#define GAME_H

#include "Board.h"

class Game {
private:
    Board board;
    bool isGameOver;

public:
    Game();
    void start();
};

#endif