#include "Game.h"
#include <iostream>

Game::Game() : board(10, 10, 10), isGameOver(false) {} // 預設 10x10 棋盤, 10 顆地雷

void Game::start() {
    std::cout << "=== 歡迎來到 C++ 踩地雷 ===" << std::endl;
    
    while (!isGameOver) {
        board.display();
        
        std::cout << "\n輸入指令 (例如 'r 3 4' 翻開, 'f 3 4' 插旗, 'q' 退出): ";
        char command;
        std::cin >> command;

        if (command == 'q') {
            std::cout << "遊戲結束！" << std::endl;
            break;
        }

        int x, y;
        std::cin >> x >> y;

        if (command == 'r') {
            bool hitMine = board.revealCell(x, y);
            if (hitMine) {
                std::cout << "\n 轟！你踩到地雷了！遊戲結束！ \n" << std::endl;
                board.display(true); // 顯示所有地雷
                isGameOver = true;
            } else if (board.checkWin()) {
                std::cout << "\n 恭喜你！找出了所有安全的格子！你贏了！ \n" << std::endl;
                board.display(true);
                isGameOver = true;
            }
        } else if (command == 'f') {
            board.flagCell(x, y);
        } else {
            std::cout << "無效的指令，請重試！" << std::endl;
            // 清除錯誤輸入狀態
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    }
}