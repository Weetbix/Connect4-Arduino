#include "Arduino.h"
#include "Board.h"
#include "Game.h"

// Given a board and a point, will determine if there is a win condition
// intersecting with the point. If so, winPoints will be populated with
// the list of 4 connected points.
// Note: Naive implementation
bool findWinFromPoint(const Board &board, const Vec2i &point, Vec2i *winPoints)
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

Game::Game() : state(State::waitingForInput),
               currentPlayer(0)
{
    resetPlayerPosition();
}

void Game::movePlayer(Direction dir)
{
    if (state == State::waitingForInput)
    {
        if (dir == Direction::left)
            player.x = (player.x - 1) % WIDTH;
        if (dir == Direction::right)
            player.x = (player.x + 1) % WIDTH;
    }
}

void Game::placePlayer()
{
    if (state == State::waitingForInput)
        state = State::running;
}

void Game::restart()
{
    p1Board = Board();
    p2Board = Board();
    state = State::waitingForInput;
    currentPlayer = 0;
    resetPlayerPosition();
}

void Game::step()
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

void Game::resetPlayerPosition()
{
    player.x = 0;
    player.y = HEIGHT - 1;
}

void Game::updatePlayerPosition()
{
    // If the next position downwards is solid,
    // then place the chip here.
    if (player.y == 0 ||
        p1Board.get(player.x, player.y - 1) == true ||
        p2Board.get(player.x, player.y - 1) == true)
    {
        Board &board = currentPlayer == 0 ? p1Board : p2Board;

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
