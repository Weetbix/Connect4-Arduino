#ifndef CONNECT_4_GAME_HPP
#define CONNECT_4_GAME_HPP

#include "Board.hpp"

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

template <int WIDTH, int HEIGHT>
class Connect4Game
{
public:
  Connect4Game() : state(State::waitingForInput),
                   currentPlayer(0)
  {
    resetPlayerPosition();
  }

  // Increment the game loop by one step
  void step()
  {
    switch (state)
    {
    case State::waitingForInput:
      break;
    case State::running:
      updatePlayerPosition();
      break;
    }
  }

  // Reset the game
  void restart()
  {
    p1Board = Board<WIDTH, HEIGHT>();
    p2Board = Board<WIDTH, HEIGHT>();
    state = State::waitingForInput;
    currentPlayer = 0;
    resetPlayerPosition();
  }

  // Move the player left or right
  void movePlayer(Direction dir)
  {
    if (state == State::waitingForInput)
    {
      if (dir == Direction::left)
        player.x = (player.x - 1) % WIDTH;
      if (dir == Direction::right)
        player.x = (player.x + 1) % WIDTH;
    }
  }

  // Drop a chip at the current player location
  void placePlayer()
  {
    if (state == State::waitingForInput)
      state = State::running;
  }

  // Gets the players current position
  const Vec2i &getPlayerPosition() const { return player; }

  // Gets the current player number
  int getPlayerNumber() const { return currentPlayer; }

  const Board<WIDTH, HEIGHT> &getPlayer1Board() const { return p1Board; }
  const Board<WIDTH, HEIGHT> &getPlayer2Board() const { return p2Board; }

  // Whether or not a player has won the current game
  const bool hasWinner() const { return state == State::winner; }

  // Gets the list of winning points as an array of 4 Vec2i objects
  Vec2i const *getWin() { return winPoints; }

private:
  // Handle a player chip falling one step
  void updatePlayerPosition()
  {
    // If the next position downwards is solid,
    // then place the chip here.
    if (player.y == 0 ||
        p1Board.get(player.x, player.y - 1) == true ||
        p2Board.get(player.x, player.y - 1) == true)
    {
      Board<WIDTH, HEIGHT> &board = currentPlayer == 0 ? p1Board : p2Board;

      // Place the chip
      board.set(player.x, player.y, true);

      // Check if there is a win from the last placed chip
      if (findWinFromPoint(board, player, winPoints))
      {
        state = State::winner;
      }
      else
      {
        resetPlayerPosition();
        currentPlayer = (currentPlayer + 1) % 2;
        state = State::waitingForInput;
      }
    }
    else
    {
      // otherwise keep moving the chip down
      player.y--;
    }
  }

  void resetPlayerPosition()
  {
    player.x = 0;
    player.y = HEIGHT - 1;
  }

  // Given a board and a point, will determine if there is a win condition
  // intersecting with the point. If so, winPoints will be populated with
  // the list of 4 connected points.
  // Note: Naive implementation
  bool findWinFromPoint(const Board<WIDTH, HEIGHT> &board, const Vec2i &point, Vec2i *winPoints)
  {
    // Check all the patterns around the point
    // iterate from minimum extent to maximum extent, checking if we have a row of 4
    int count = 0;
    int x, y;
    for (x = point.x - 3; x < point.x + 3; x++)
    {
      if (board.get(x, point.y))
      {
        winPoints[count] = Vec2i(x, point.y);
        count++;
      }
      else
      {
        count = 0;
      }

      if (count >= 4)
        return true;
    }

    count = 0;
    for (y = point.y - 3; y < point.y + 3; y++)
    {
      if (board.get(point.x, y))
      {
        winPoints[count] = Vec2i(point.x, y);
        count++;
      }
      else
      {
        count = 0;
      }

      if (count >= 4)
        return true;
    }

    // Bottom left -> top right
    count = 0;
    for (x = point.x - 3, y = point.y - 3;
         x < point.x + 3 && y < point.y + 3;
         x++, y++)
    {
      if (board.get(x, y))
      {
        winPoints[count] = Vec2i(x, y);
        count++;
      }
      else
      {
        count = 0;
      }

      if (count >= 4)
        return true;
    }

    // Bottom right -> top left
    for (x = point.x + 3, y = point.y - 3;
         x > point.x - 3 && y < point.y + 3;
         x--, y++)
    {
      if (board.get(x, y))
      {
        winPoints[count] = Vec2i(x, y);
        count++;
      }
      else
      {
        count = 0;
      }

      if (count >= 4)
        return true;
    }

    // No matches
    return false;
  }

  // Our board data
  Board<WIDTH, HEIGHT> p1Board;
  Board<WIDTH, HEIGHT> p2Board;

  int currentPlayer;
  State state;

  // Player position
  Vec2i player;

  // Array of the winning 4 connected points (if the game is won)
  Vec2i winPoints[4];
};

#endif