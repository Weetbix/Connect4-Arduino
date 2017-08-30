
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
  running,
  winner
};

class Game
{
public:
  Game();

  // Increment the game loop by one step
  void step();

  // Reset the game
  void restart();

  // Move the player left or right
  void movePlayer(Direction dir);

  // Drop a chip at the current player location
  void placePlayer();

  // Gets the players current position
  const Vec2i &getPlayerPosition() const { return player; }

  // Gets the current player number
  int getPlayerNumber() const { return currentPlayer; }

  const Board &getPlayer1Board() const { return p1Board; }
  const Board &getPlayer2Board() const { return p2Board; }

  // Whether or not a player has won the current game
  const bool hasWinner() const { return state == State::winner; }

  // Gets the list of winning points as an array of 4 Vec2i objects
  Vec2i const *getWin() { return winPoints; }

private:
  // Handle a player chip falling one step
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
  State state;

  // Player position
  Vec2i player;

  // Array of the winning 4 connected points (if the game is won)
  Vec2i winPoints[4];
};

#endif