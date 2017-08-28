#ifndef LED_BOARD_RENDERER_H
#define LED_BOARD_RENDERER_H

#include <LedControl.h>
#include "ConnectBoard.h"

void render(LedControl &led, const ConnectBoard &board)
{
    const bool *data = board.getBoard();

    for (int y = 0; y < 8; y++)
    {
        byte row = 0;
        for (int x = 0; x < 8; x++)
        {
            row |= data[(y % 8) + (x * 8)] << 7 - x;
        }
        led.setRow(0, y, row);
    }

    const Vec2i &playerPos = board.getPlayerPosition();
    led.setLed(0, playerPos.x, playerPos.y, true);
}

#endif