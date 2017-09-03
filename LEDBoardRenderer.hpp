#ifndef LED_BOARD_RENDERER_HPP
#define LED_BOARD_RENDERER_HPP

#include <LedControl.h>
#include "Board.hpp"

void renderPlayer(LedControl &led, const Vec2i &pos)
{
    led.setLed(0, pos.x, pos.y, true);
}

template <int WIDTH, int HEIGHT>
void renderBoard(LedControl &led, const Board<WIDTH, HEIGHT> &board)
{
    const bool *data = board.getData();

    for (int y = 0; y < HEIGHT; y++)
    {
        byte row = 0;
        for (int x = 0; x < WIDTH; x++)
        {
            // The rows and columns are backwards due to the mounting position
            row |= data[(y % HEIGHT) + (x * WIDTH)] << 7 - x;
        }
        led.setRow(0, y, row);
    }
}

template <int WIDTH, int HEIGHT>
void renderBoards(LedControl &led, const Board<WIDTH, HEIGHT> &board1, const Board<WIDTH, HEIGHT> &board2)
{
    const bool *data1 = board1.getData();
    const bool *data2 = board2.getData();

    for (int y = 0; y < HEIGHT; y++)
    {
        byte row = 0;
        for (int x = 0; x < WIDTH; x++)
        {
            // The rows and columns are backwards due to the mounting position
            row |= (data1[(y % HEIGHT) + (x * WIDTH)] || data2[(y % HEIGHT) + (x * WIDTH)]) << 7 - x;
        }
        led.setRow(0, y, row);
    }
}

#endif