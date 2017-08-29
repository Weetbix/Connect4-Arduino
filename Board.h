
#ifndef BOARD_H
#define BOARD_H

#include "Arduino.h"

const int WIDTH = 8;
const int HEIGHT = 8;

class Board
{
  public:
    const bool *getData() const;

    void set(const int &x, const int &y, const bool &val);
    bool get(const int &x, const int &y) const;

  private:
    // Board width and height, can be made
    // configurable through the constructor later
    const static int WIDTH = 8;
    const static int HEIGHT = 8;

    // Our board data
    bool board[WIDTH * HEIGHT];
};

#endif