#include<bits/stdc++.h>

using namespace std;

enum class CellValue { Empty, One, Two, Three, Four, Five, Six, Seven, Eight, Mine, Invalid };
enum class CellState { Hidden, Opened, Marked };

class GameManager;

// Class representing an individual cell in the Minesweeper board
class Cell {
private:
    CellValue value;
    CellState state;

public:
    Cell() : value(CellValue::Empty), state(CellState::Hidden) {}

    CellValue getValue() const { return value; }
    void setValue(CellValue newValue) { value = newValue; }

    CellState getState() const { return state; }
    void setState(CellState newState) { state = newState; }

    void displayCharacter() const; // Function to display the cell based on its state and value represented by characters
};
    // Function to display the character representing the cell based on its state and value
    void Cell::displayCharacter() const {
        switch (state) {
            case CellState::Hidden:
                cout << " -";
                break;
            case CellState::Marked:
                cout << "\033[31m M\033[0m";  // Red Font color
                break;
            case CellState::Opened:
                switch (value) {
                    case CellValue::Mine:
                        cout << "\033[41m *\033[0m";  // Bright Red Background color
                        break;
                    case CellValue::Empty:
                        cout << "\033[37m 0\033[0m";   // Default White Font color
                        break;
                    case CellValue::One:
                        cout << "\033[34m 1\033[0m";  // Blue Font color
                        break;
                    case CellValue::Two:
                        cout << "\033[32m 2\033[0m";  // Green Font color
                        break;
                    case CellValue::Three:
                        cout << "\033[91m 3\033[0m";  // Red Font color
                        break;
                    case CellValue::Four:
                        cout << "\033[35m 4\033[0m";  // Magenta Font color
                        break;
                    case CellValue::Five:
                        cout << "\033[33m 5\033[0m";  // Yellow Font color
                        break;
                    case CellValue::Six:
                        cout << "\033[36m 6\033[0m";  // Cyan Font color
                        break;
                    case CellValue::Seven:
                        cout << "\033[92m 7\033[0m";  // Bright Green Font color
                        break;
                    case CellValue::Eight:
                        cout << "\033[94m 8\033[0m";  // Bright Blue Font color
                        break;
                    default:
                        cout << ' '; // Should not reach here
                        break;
                }
                break;
            default:
                cout << ' '; // Should not reach here
                break;
        }
    }
// Class representing the Minesweeper board
class Board {
private:
    int size;
    int mines;

    bool isValid(int row, int col) const;
    bool isMine(int row, int col) const;
    int countAdjacentMines(int row, int col) const;
    void openSpaces(int x, int y);

public:
    Board(int boardSize, int numMines) : size(boardSize), mines(numMines), cells(boardSize, vector<Cell>(boardSize)) {}
    vector<vector<Cell>> cells;
    // Function to randomly place mines on the board
    void placeMines() {
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
    void setNumbers() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (!isMine(i, j)) {
                    int count = countAdjacentMines(i, j);
                    cells[i][j].setValue(static_cast<CellValue>(count));
                }
            }
        }
    }

    int getSize() const { return size; }
    int getNumMines() const { return mines; }
    CellState getCellState(int row, int col) const { return cells[row][col].getState(); }
    CellValue getCellValue(int row, int col) const { return cells[row][col].getValue(); }

    void initialize();
    void revealAllMines();
    void openCell(int x, int y, GameManager& gameManager);
    void printBoard() const;
};
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
// Class representing the Minesweeper game manager
class GameManager {
private:
    bool isGameOver;
    bool isGameWon;
    Board board;

    void chooseDifficulty();

public:
    GameManager(int boardSize, int numMines) : isGameOver(false), isGameWon(false), board(boardSize, numMines) {}

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
// Main function to run the Minesweeper game
int main() {
    GameManager gameManager(0, 0);
    gameManager.playGame();

    return 0;
}
