#include <LedControl.h>
#include <binary.h>

#include "Game.h"
#include "LEDBoardRenderer.h"

// LED matrix pins
const int DATA_PIN = 12;
const int CLOCK_PIN = 11;
const int CS_PIN = 10;

// Button pins
const int MOVE_BUTTON_PIN = 6;
const int OKAY_BUTTON_PIN = 7;

LedControl led = LedControl(
    DATA_PIN,
    CLOCK_PIN,
    CS_PIN,
    // One device
    1);

Game game = Game();

void setup()
{
    // Wake up the device
    led.shutdown(0, false);
    led.setIntensity(0, 0);

    // Activate internal pull up resistors for button pins
    pinMode(MOVE_BUTTON_PIN, INPUT_PULLUP);
    pinMode(OKAY_BUTTON_PIN, INPUT_PULLUP);
}

void playingLoop()
{
    if (digitalRead(MOVE_BUTTON_PIN) == LOW)
    {
        game.movePlayer(Direction::right);
    }

    if (digitalRead(OKAY_BUTTON_PIN) == LOW)
    {
        game.placePlayer();
    }

    // Render player ones chips first, so they are solid
    renderBoard(led, game.getPlayer1Board());
    // If we are player one, render the player in both frames
    if (game.getPlayerNumber() == 0)
    {
        renderPlayer(led, game.getPlayerPosition());
    }
    delay(50);

    // Frame two, render both players chips. This makes player
    // twos chips flash.
    renderBoards(led, game.getPlayer1Board(), game.getPlayer2Board());
    renderPlayer(led, game.getPlayerPosition());
    delay(50);

    game.step();
}

void winnerLoop()
{
    // Handle leaving the winning screen
    if (digitalRead(MOVE_BUTTON_PIN) == LOW ||
        digitalRead(OKAY_BUTTON_PIN) == LOW)
    {
        // Slowly wipe the screen
        for (int row = 7; row >= 0; row--)
        {
            led.setColumn(0, row + 2, B00000000);
            led.setColumn(0, row + 1, row % 2 == 0 ? B01010101 : B10101010);
            led.setColumn(0, row, B11111111);
            delay(100);
        }
        game.restart();
        return;
    }

    // Handle flashing the winning points
    const Vec2i *win = game.getWin();

    // First render all the boards as solid
    renderBoards(led, game.getPlayer1Board(), game.getPlayer2Board());
    // but turn off the winning line
    for (int i = 0; i < 4; i++)
    {
        led.setLed(0, win[i].x, win[i].y, false);
    }
    delay(100);

    // Now render the winning line, so it flashes
    for (int i = 0; i < 4; i++)
    {
        led.setLed(0, win[i].x, win[i].y, true);
    }

    delay(100);
}

void loop()
{
    if (game.hasWinner())
    {
        winnerLoop();
    }
    else
    {
        playingLoop();
    }
}