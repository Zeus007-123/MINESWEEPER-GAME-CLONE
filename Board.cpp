// Board.cpp
#include "Board.h"
#include "GameManager.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <queue>

using namespace std;

Board::Board(int boardSize, int numMines) : size(boardSize), mines(numMines), cells(boardSize, std::vector<Cell>(boardSize)) {}

// Function to check if a cell is valid on the board
bool Board::isValid(int row, int col) const {
    return row >= 0 && row < size && col >= 0 && col < size;
}
// Function to check if a cell contains a mine
bool Board::isMine(int row, int col) const {
    return cells[row][col].getValue() == CellValue::Mine;
}
// Function to count the number of adjacent mines for a cell
int Board::countAdjacentMines(int row, int col) const {
    int count = 0;

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int newRow = row + i;
            int newCol = col + j;

            if (isValid(newRow, newCol) && isMine(newRow, newCol)) {
                ++count;
            }
        }
    }

    return count;
}
// Function to open adjacent empty spaces using BFS
void Board::openSpaces(int x, int y) {
    queue<int> rowQueue;
    queue<int> colQueue;

    rowQueue.push(x);
    colQueue.push(y);

    while (!rowQueue.empty() && !colQueue.empty()) {
        int row = rowQueue.front();
        int col = colQueue.front();
        rowQueue.pop();
        colQueue.pop();

        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int newRow = row + i;
                int newCol = col + j;

                if (isValid(newRow, newCol) && cells[newRow][newCol].getState() == CellState::Hidden) {
                    cells[newRow][newCol].setState(CellState::Opened);

                    if (cells[newRow][newCol].getValue() == CellValue::Empty) {
                        rowQueue.push(newRow);
                        colQueue.push(newCol);
                    }
                }
            }
        }
    }
}
// Function to randomly place mines on the board
void Board::placeMines() {
    srand(time(nullptr));

    vector<vector<bool>> mineLocations(size, vector<bool>(size, false));

    for (int i = 0; i < mines; ++i) {
        int randomX, randomY;

        do {
            randomX = rand() % size;
            randomY = rand() % size;
        } while (mineLocations[randomX][randomY]);

        mineLocations[randomX][randomY] = true;
        cells[randomX][randomY].setValue(CellValue::Mine);
    }
}
// Function to set numbers on cells indicating adjacent mines
void Board::setNumbers() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (!isMine(i, j)) {
                int count = countAdjacentMines(i, j);
                cells[i][j].setValue(static_cast<CellValue>(count));
            }
        }
    }
}
int Board::getSize() const {
    return size;
}

int Board::getNumMines() const {
    return mines;
}

CellState Board::getCellState(int row, int col) const {
    return cells[row][col].getState();
}

CellValue Board::getCellValue(int row, int col) const {
    return cells[row][col].getValue();
}
// Function to initialize the board with hidden cells
void Board::initialize() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cells[i][j] = Cell();
        }
    }
}
// Function to reveal all mines at the end of the game
void Board::revealAllMines() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (cells[i][j].getValue() == CellValue::Mine) {
                cells[i][j].setState(CellState::Opened);
            }
        }
    }
}
// Function to open a cell based on user input 
void Board::openCell(int x, int y, GameManager& gameManager) {
    if (!isValid(x, y)) {
        cout << "Invalid move! Please enter valid coordinates." << endl;
        cout<<endl<< endl;
        return;
    }

    Cell& currentCell = cells[x][y];

    if (currentCell.getState() == CellState::Opened) {
        cout << "Cell already opened. Choose another move." << endl;
        cout<<endl<< endl;
        return;
    }

    if (currentCell.getState() == CellState::Marked) {
        cout << "Cell is marked. Unmark before opening." << endl;
        cout<<endl<< endl;
        return;
    }

    currentCell.setState(CellState::Opened);

    if (currentCell.getValue() == CellValue::Mine) {
        // Game over if a mine is opened
        gameManager.gameOver();
    } else if (currentCell.getValue() == CellValue::Empty) {
        // Open empty spaces if the cell is empty
        openSpaces(x, y);
    }
}
// Function to print the current state of the board
void Board::printBoard() const {
    cout << "   ";
    for (int i = 0; i < size; ++i) {
        cout << "  " << i << " ";
    }
    cout << "\n   ";
    for (int i = 0; i < size; ++i) {
        cout << "+---";
    }
    cout << "+\n";

    for (int i = 0; i < size; ++i) {
        cout << " " << i << " |";
        for (int j = 0; j < size; ++j) {
            cells[i][j].displayCharacter();
            cout << " |";
        }
        cout << "\n   ";
        for (int j = 0; j < size; ++j) {
            cout << "+---";
        }
        cout << "+\n";
    }

    cout << endl;
}
