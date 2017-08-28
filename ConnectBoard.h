
#ifndef CONNECT_BOARD_H
#define CONNECT_BOARD_H

#include "Arduino.h"

const int WIDTH = 8;
const int HEIGHT = 8;

struct Vec2i
{
  Vec2i() : x(0), y(0){};
  int x;
  int y;
};

enum Direction
{
  left,
  right
};

enum State
{
  waitingForInput,
  Running
};

class ConnectBoard
{
public:
  ConnectBoard();

  const bool *getBoard() const;

  void step();

  void movePlayer(Direction dir);
  void placePlayer();

  const Vec2i &getPlayerPosition() const { return player; }

private:
  void set(const int &x, const int &y, const bool &val);
  bool get(const int &x, const int &y) const;

  void updatePlayerPosition();
  void resetPlayerPosition();

  // Board width and height, can be made
  // configurable through the constructor later
  const static int WIDTH = 8;
  const static int HEIGHT = 8;

  // Our board data
  bool board[WIDTH * HEIGHT];

  Vec2i player;
  State state;
};

#endif