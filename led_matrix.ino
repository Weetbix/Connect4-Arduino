#include <LedControl.h>
#include <binary.h>

#include "ConnectBoard.h"
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

ConnectBoard board = ConnectBoard();

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
        board.movePlayer(Direction::right);
    }

    if (digitalRead(OKAY_BUTTON_PIN) == LOW)
    {
        board.placePlayer();
    }

    // led.setLed(0, 0, 0, board.getState());
    // led.setLed(0, 0, 0, true);
    render(led, board);
    // board.movePlayer(Direction::right);
    board.step();
    delay(200);
}