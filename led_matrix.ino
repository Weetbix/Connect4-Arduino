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

void loop()
{
    if (digitalRead(MOVE_BUTTON_PIN) == LOW)
    {
        game.movePlayer(Direction::right);
    }

    if (digitalRead(OKAY_BUTTON_PIN) == LOW)
    {
        game.placePlayer();
    }

    if (game.hasWinner())
    {
        led.clearDisplay(0);
        led.setRow(0, 0, B01010101);
        return;
    }

    // led.clearDisplay(0);
    renderBoard(led, game.getPlayer1Board());
    // Only render player 1 as a solid dot
    if (game.getPlayerNumber() == 0)
    {
        renderPlayer(led, game.getPlayerPosition());
    }
    delay(50);
    renderBoards(led, game.getPlayer1Board(), game.getPlayer2Board());
    renderPlayer(led, game.getPlayerPosition());
    delay(50);

    // TODO: Change rendering to use timers rather than stopping the loop

    // board.movePlayer(Direction::right);
    game.step();
}