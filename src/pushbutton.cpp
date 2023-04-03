/**
 * @file pushbutton.cpp
 *
 * This library helps you determine how the user interact with your push button.
 *
 * @author Alexandre Maurer (alexmaurer@madis.ch)
 * @license MIT
 *
 */

#include "pushbutton.h"

/**
 * @brief Construct a new Push Button:: Push Button object
 *
 * @param pin the input pin
 * @param pressed_state HIGH (default) or LOW : polarity of the signal when your
 * switch is in the pressed state.
 * @param read_cycle_ms interval in ms when the input is read (default 20ms)
 */
PushButton::PushButton(int pin, int pressed_state, int read_cycle_ms) {
  pressed_state_ = pressed_state;
  pin_ = pin;
  read_cycle_ms_ = read_cycle_ms;

  last_time_ = millis();
  last_digital_read_ = digitalRead(pin_);
};

/**
 * @brief To be called within your loop()
 *
 */
void PushButton::update(void) {
  if ((millis() - last_time_) < (unsigned long)read_cycle_ms_)
    return;

  last_time_ = millis();

  if (rising_.eventOccured) {
    unsigned long delta = millis() - rising_.time;

    if (delta > 2000) {
      rising_.eventOccured = false;
      state_ = State::longPress;
      return;
    }
  }

  int read = digitalRead(pin_);
  if (last_digital_read_ != read) {
    last_digital_read_ = read;

    if (read == pressed_state_) {
      rising_.time = millis();
      rising_.eventOccured = true;
    } else {
      if (rising_.eventOccured) {
        rising_.eventOccured = false;
        state_ = State::shortPress;
      }
    }
  }
}

/**
 * @brief Return button state and reset internal state
 *
 * @return PushButton::State
 */
PushButton::State PushButton::pressed(void) {
  State s = state_;
  state_ = State::nothing;

  //   if ((int)s == 1 || (int)s == 2)
  //     Serial.printf("state %u", s);
  return s;
}