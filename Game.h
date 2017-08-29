
#ifndef CONNECT_BOARD_H
#define CONNECT_BOARD_H

#include "Arduino.h"
#include "Board.h"

struct Vec2i
{
  Vec2i() : x(0), y(0){};
  Vec2i(int x, int y) : x(x), y(y){};
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
  Running,
  Winner
};

class Game
{
public:
  Game();

  const bool *getBoard() const;

  void step();

  void movePlayer(Direction dir);
  void placePlayer();

  const Vec2i &getPlayerPosition() const { return player; }
  int getPlayerNumber() const { return currentPlayer; }

  const Board &getPlayer1Board() const { return p1Board; }
  const Board &getPlayer2Board() const { return p2Board; }

  const bool hasWinner() const { return state == State::Winner; }
  Vec2i const *getWin() { return winPoints; }

private:
  void updatePlayerPosition();
  void resetPlayerPosition();

  // Board width and height, can be made
  // configurable through the constructor later
  const static int WIDTH = 8;
  const static int HEIGHT = 8;

  // Our board data
  Board p1Board;
  Board p2Board;

  int currentPlayer;
  Vec2i lastMove;
  Vec2i player;
  Vec2i winPoints[4];
  State state;
};

#endif