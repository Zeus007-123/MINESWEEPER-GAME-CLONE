// Cell.cpp
#include "Cell.h"
using namespace std;

Cell::Cell() : value(CellValue::Empty), state(CellState::Hidden) {}

CellValue Cell::getValue() const {
    return value;
}

void Cell::setValue(CellValue newValue) {
    value = newValue;
}

CellState Cell::getState() const {
    return state;
}

void Cell::setState(CellState newState) {
    state = newState;
}
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