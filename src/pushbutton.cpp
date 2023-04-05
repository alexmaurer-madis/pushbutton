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
 * @brief Construct a new Push Button. call setPin before use.
 *
 */
PushButton::PushButton(void) { last_time_ = millis(); }

/**
 * @brief Construct a new Push Button. The pin must already be configured as an
 * input.
 *
 * @param pin the input pin number
 * @param pressed_state HIGH (default) or LOW : polarity of the signal when your
 * button is pressed
 * @param long_press_ms The time in ms the button must be pressed to trigger a
 * long press
 * @param read_interval_ms interval in ms between each time the input is read
 * (default 20ms)
 */
PushButton::PushButton(int pin, int pressed_state, int long_press_ms,
                       int read_interval_ms) {
  pin_ = pin;
  pressed_state_ = pressed_state;
  long_press_ms_ = long_press_ms;
  read_interval_ms_ = read_interval_ms;

  last_time_ = millis();
  last_digital_read_ = digitalRead(pin_);
  init_ = true;
};

/**
 * @brief Set the corresponding pin of the push button
 *
 * @param pin Pin number
 * @param mode Pin mode, genrally INPUT (default) or INPUT_PULLUP
 * @param pressed_state LOW or HIGH. Pin input level when the push button is
 * pressed (default HIGH)
 * @param long_press_ms The time in ms the button must be pressed to trigger a
 * long press (default 2000ms)
 */
void PushButton::setPin(uint8_t pin, uint8_t mode, int pressed_state,
                        int long_press_ms) {
  pin_ = pin;
  pinMode(pin, mode);
  pressed_state_ = pressed_state;
  long_press_ms_ = long_press_ms;

  last_digital_read_ = digitalRead(pin_);
  init_ = true;
}

/**
 * @brief Return the current read interval value
 *
 * @return int read interval in ms
 */
int PushButton::getReadInterval(void) { return read_interval_ms_; }

/**
 * @brief Set the interval between each time the input pin is read
 *
 * @param read_cycle_ms interval in ms
 */
void PushButton::setReadInterval(int read_interval_ms) {
  read_interval_ms_ = read_interval_ms;
}

/**
 * @brief To be called within your loop()
 *
 */
void PushButton::update(void) {
  if (!init_)
    return;

  if ((millis() - last_time_) < (unsigned long)read_interval_ms_)
    return;

  last_time_ = millis();

  if (rising_.eventOccured) {
    unsigned long delta = millis() - rising_.time;

    if (delta > long_press_ms_) {
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
 * @brief Return the button state
 *
 * @return PushButton::State
 */
PushButton::State PushButton::getState(void) {
  State s = state_;
  state_ = State::nothing;

  return s;
}

/**
 * @brief Return the current long press duration
 *
 * @return int duration in ms
 */
int PushButton::getLongPressDuration(void) { return long_press_ms_; }

/**
 * @brief Set the time the button must be pressed to trigger a long press
 *
 * @param long_press_ms time in ms
 */
void PushButton::setLongPressDuration(int long_press_ms) {
  long_press_ms_ = long_press_ms;
}