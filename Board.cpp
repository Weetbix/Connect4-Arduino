#include "Arduino.h"
#include "Board.h"

void Board::set(const int &x, const int &y, const bool &val)
{
    const int index = (x % WIDTH) + (y * HEIGHT);
    board[index] = val;
}

bool Board::get(const int &x, const int &y) const
{
    // Return false for values outside of the board
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return false;

    return board[(x % WIDTH) + (y * HEIGHT)];
}

const bool *Board::getData() const
{
    return board;
}
