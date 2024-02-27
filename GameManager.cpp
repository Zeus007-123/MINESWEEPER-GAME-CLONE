// GameManager.cpp
#include "GameManager.h"
#include <iostream>

using namespace std;

GameManager::GameManager(int boardSize, int numMines) : isGameOver(false), isGameWon(false), board(boardSize, numMines) {}

// Function to start a new game
void GameManager::startGame() {
    displayGameTitle();
    displayGameIntro();
    chooseDifficulty();
    board.initialize();
    do {
        board.placeMines();
    } while (board.getCellValue(0, 0) == CellValue::Mine);
    board.setNumbers();
    isGameOver = false;
    isGameWon = false;
}
// Function to display the current status of the game
void GameManager::displayGameStatus() const {
    cout << "-----------------------------\n";
    cout << "          Minesweeper         \n";
    cout << "-----------------------------\n";
    cout << endl << endl;
    board.printBoard();
}
// Function to check if the game is over
bool GameManager::checkGameOver() const {
    return isGameOver;
}
// Function to check if the game is won
bool GameManager::checkGameWon() const {
    return isGameWon;
}
// Function to end the game and display the result
void GameManager::endGame() {
    displayGameStatus();

    if (checkGameWon()) {
      cout<<"+-------------------------------------------+"<<endl;
      cout<<"|      CONGRATULATIONS ... YOU WON !!!      |"<<endl;
      cout<<"+-------------------------------------------+"<<endl<<endl;
      cout<<"+-------------------------------------------+"<<endl;
      cout<<"|                 GAME OVER                 |"<<endl;
      cout<<"|                 THANK YOU                 |"<<endl;
      cout<<"|              SEE YOU NEXT TIME            |"<<endl;
      cout<<"+-------------------------------------------+"<<endl;
    } else {
      cout<<"+----------------------------------------------------+"<<endl;
      cout<<"|    OOPS! YOU STEPPED ON A MINE ... YOU LOSE !!!    |"<<endl;
      cout<<"+----------------------------------------------------+"<<endl<<endl;
      cout<<"+-------------------------------------------+"<<endl;
      cout<<"|                 GAME OVER                 |"<<endl;
      cout<<"|                 THANK YOU                 |"<<endl;
      cout<<"|              SEE YOU NEXT TIME            |"<<endl;
      cout<<"+-------------------------------------------+"<<endl;
    }
}
// Function to handle the player's move
void GameManager::handleMove() {
    int x, y;
    int operation;  // 1 for Open, 2 for Mark/Unmark

    cout << "Enter row and column (space-separated): ";
    cin >> x >> y;
    cout << endl;
    cout << "Choose operation (1 for Open, 2 for Mark/Unmark): ";
    cin >> operation;
    cout << endl << endl;

    if (operation == 1) {
        board.openCell(x, y, *this);
    } else if (operation == 2) {
        CellState currentState = board.getCellState(x, y);

        if (currentState == CellState::Opened) {
            cout << "Cannot mark an already opened cell." << endl;
            cout<< endl<< endl;
        } else {
            if (currentState == CellState::Hidden) {
                board.cells[x][y].setState(CellState::Marked);
            } else if (currentState == CellState::Marked) {
                board.cells[x][y].setState(CellState::Hidden);
            }
        }
    } else {
        cout << "Invalid operation. Please choose 1 for Open or 2 for Mark/Unmark." << endl;
        cout<< endl << endl;
    }

    checkForWin();
}
// Function to handle the game over scenario
void GameManager::gameOver() {
    isGameOver = true;
    board.revealAllMines();
    endGame();
}
// Function to check if the game is won and end the game if so
void GameManager::checkForWin() {
    if (!isGameOver) {
        int size = board.getSize();

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (board.getCellState(i, j) != CellState::Opened && board.getCellValue(i, j) != CellValue::Mine) {
                    return;
                }
            }
        }

        isGameWon = true;
        endGame();
    }
}
// Function to play the Minesweeper game
void GameManager::playGame() {
    startGame();

    while (!checkGameOver() && !checkGameWon()) {
        displayGameStatus();
        handleMove();
    }
}
// Function to display the Minesweeper game title
void GameManager::displayGameTitle() const {
    cout << endl;
    cout << "\033[1;34m  █▄ ▄█ ▀█▀ █▄  █ █▀▀▀  █▀▀▀ █ ▄ █ █▀▀▀ █▀▀▀"
            " █▀▀▄ █▀▀▀ █▀▀▄\033[0m"
         << endl;
    cout << "\033[1;34m  █ █ █  █  █ █ █ █▀▀▀  ▀▀▄▄ █ █ █ █▀▀▀ █▀▀▀ █▄▄▀ █▀▀▀ █▄▄▀\033[0m"
         << endl;
    cout << "\033[1;34m  █   █ ▄█▄ █  ▀█ █▄▄▄  ▄▄▄█ ▀█▀█▀ █▄▄▄ █▄▄▄ █   "
            " █▄▄▄ █ ▀▄\033[0m"
         << endl;
    cout << "  ----- --- ----- ----  ---- ----- ---- ---- ---- ---- ----"
         << endl;
    cout << endl;
}
// Function to display the Minesweeper game introduction and rules
void GameManager::displayGameIntro() const {
    cout << "\033[31m[Rules]\033[0m\n\n";
    cout << "1. The board is divided into cells, with mines randomly distributed.\n";
    cout << "2. To win, you need to open all the cells.\n";
    cout << "3. The number on a cell shows the number of mines adjacent to it.\n";
    cout << "4. Using this information, you can determine cells that are safe, and cells that contain mines.\n";
    cout << "5. Interact, evolve and enjoy!\n\n";
    cout << "\033[31m[HOW TO PLAY]\033[0m" << endl << endl;
    cout << "1. Player is to give x and y coordinate of the cell as first two inputs" << endl;
    cout << "2. The next input is to open or mark the cell" << endl;
    cout << "3. Numbers on the cells indicate the number of mines around the cell" << endl;
  cout<<endl<<endl;
  cout<<"+-------------------------------------------+"<<endl;
  cout<<"|                GAME STARTS                |"<<endl;
  cout<<"+-------------------------------------------+"<<endl<<endl;
  cout<<"WELCOME TO MINESWEEPER !!!"<<endl;
}
// Function to choose the difficulty level of the game
void GameManager::chooseDifficulty() {
    int difficulty;

    while (true) {
        cout << "Choose difficulty level:\n\n";
        cout << "\033[32m1. Beginner (9x9 board with 10 mines)\033[0m\n";
        cout << "\033[38;5;202m2. Intermediate (16x16 board with 40 mines)\033[0m\n";
        cout << "\033[35m3. Advanced (24x24 board with 99 mines)\033[0m\n\n";
        cout << "Enter the corresponding number (1-3): ";
        cin >> difficulty;
        cout << endl << endl;

        switch (difficulty) {
            case 1:
                board = Board(9, 10);
                return;
            case 2:
                board = Board(16, 40);
                return;
            case 3:
                board = Board(24, 99);
                return;
            default:
                cerr << "Invalid difficulty level. Please enter a valid difficulty level.\n";
        }
    }
}