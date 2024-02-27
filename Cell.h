// Cell.h
#ifndef CELL_H
#define CELL_H

#pragma once

#include <iostream>

enum class CellValue { Empty, One, Two, Three, Four, Five, Six, Seven, Eight, Mine, Invalid };
enum class CellState { Hidden, Opened, Marked };

class Cell {
private:
    CellValue value;
    CellState state;

public:
    Cell();
    CellValue getValue() const;
    void setValue(CellValue newValue);
    CellState getState() const;
    void setState(CellState newState);
    void displayCharacter() const;
};

#endif // CELL_H