// Board.h
#ifndef BOARD_H
#define BOARD_H

#pragma once

#include "Cell.h"
#include <vector>

using namespace std;

class GameManager;  // Forward declaration

class Board {
private:
    int size;
    int mines;

    bool isValid(int row, int col) const;
    bool isMine(int row, int col) const;
    int countAdjacentMines(int row, int col) const;
    void openSpaces(int x, int y);

public:
    Board(int boardSize, int numMines);
    
    vector<vector<Cell>> cells;
    void placeMines();
    void setNumbers();
    int getSize() const;
    int getNumMines() const;
    CellState getCellState(int row, int col) const;
    CellValue getCellValue(int row, int col) const;
    void initialize();
    void revealAllMines();
    void openCell(int x, int y, GameManager& gameManager);
    void printBoard() const;
};

#endif // BOARD_H