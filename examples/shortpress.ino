#include <Arduino.h>
#include <pushbutton.h>

PushButton pushBtn;

void setup() {
  Serial.begin(9600);

  // Pushbutton on pin 4
  // Set pin mode as input with pull-up.
  // Signal is LOW when button is pressed
  // The button must be held down for 4s to trigger a long press
  pushBtn.setPin(4, INPUT_PULLUP, LOW, 4000);
}

void loop() {
  pushBtn.process();

  switch (pushBtn.getState()) {
  case PushButton::State::shortPress:
    Serial.println("Short press");
    break;

  case PushButton::State::longPress:
    Serial.println("Long press");
    break;
  }
}
