#ifndef LED_BOARD_RENDERER_H
#define LED_BOARD_RENDERER_H

#include <LedControl.h>
#include "Board.h"

void renderPlayer(LedControl &led, const Vec2i &pos)
{
    led.setLed(0, pos.x, pos.y, true);
}

void renderBoard(LedControl &led, const Board &board)
{
    const bool *data = board.getData();

    for (int y = 0; y < 8; y++)
    {
        byte row = 0;
        for (int x = 0; x < 8; x++)
        {
            // The rows and columns are backwards due to the mounting position
            row |= data[(y % 8) + (x * 8)] << 7 - x;
        }
        led.setRow(0, y, row);
    }
}

void renderBoards(LedControl &led, const Board &board1, const Board &board2)
{
    const bool *data1 = board1.getData();
    const bool *data2 = board2.getData();

    for (int y = 0; y < 8; y++)
    {
        byte row = 0;
        for (int x = 0; x < 8; x++)
        {
            // The rows and columns are backwards due to the mounting position
            row |= (data1[(y % 8) + (x * 8)] || data2[(y % 8) + (x * 8)]) << 7 - x;
        }
        led.setRow(0, y, row);
    }
}

#endif