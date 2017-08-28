#include "Arduino.h"
#include "ConnectBoard.h"

ConnectBoard::ConnectBoard() : state(State::waitingForInput)
{
    resetPlayerPosition();
}

void ConnectBoard::movePlayer(Direction dir)
{
    if (dir == Direction::left)
        player.x = (player.x - 1) % WIDTH;
    if (dir == Direction::right)
        player.x = (player.x + 1) % WIDTH;
}

void ConnectBoard::placePlayer()
{
    state = State::Running;
}

void ConnectBoard::step()
{
    switch (state)
    {
    case State::waitingForInput:
        break;
    case State::Running:
        updatePlayerPosition();
        break;
    }
}

void ConnectBoard::resetPlayerPosition()
{
    player.x = 0;
    player.y = HEIGHT - 1;
}

void ConnectBoard::updatePlayerPosition()
{
    if (player.y == 0 ||
        get(player.x, player.y - 1) == true)
    {
        set(player.x, player.y, true);
        resetPlayerPosition();
        state = State::waitingForInput;
    }
    else
    {
        player.y--;
    }
}

void ConnectBoard::set(const int &x, const int &y, const bool &val)
{
    const int index = (x % WIDTH) + (y * HEIGHT);
    board[index] = val;
}

bool ConnectBoard::get(const int &x, const int &y) const
{
    return board[(x % WIDTH) + (y * HEIGHT)];
}

const bool *ConnectBoard::getBoard() const
{
    return board;
}
