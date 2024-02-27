// GameManager.h
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#pragma once

#include "Board.h"

class GameManager {
private:
    bool isGameOver;
    bool isGameWon;
    Board board;

    void chooseDifficulty();

public:
    GameManager(int boardSize, int numMines);
    void startGame();
    void displayGameStatus() const;
    bool checkGameOver() const;
    bool checkGameWon() const;
    void endGame();
    void handleMove();
    void gameOver();
    void checkForWin();
    void playGame();
    void displayGameTitle() const;
    void displayGameIntro() const;
};

#endif // GAME_MANAGER_H