/**
 * @file pushbutton.h
 *
 * This library helps you determine how the user interact with your push button.
 *
 * @author Alexandre Maurer (alexmaurer@madis.ch)
 * @license MIT
 *
 */

#ifndef __PUSHBUTTON_H
#define __PUSHBUTTON_H

#include <Arduino.h>

class PushButton {

public:
  enum class State { nothing, shortPress, longPress };

  PushButton(void);
  PushButton(int pin, int pressed_state = HIGH, int long_press_ms = 2000,
             int read_cycle_ms = 20);

  void setPin(uint8_t pin, uint8_t mode = INPUT, int pressed_state = HIGH,
              int long_press_ms = 2000);

  int getReadInterval(void);
  void setReadInterval(int read_cycle_ms);

  int getLongPressDuration(void);
  void setLongPressDuration(int long_press_ms);

  void update(void);
  State getState(void);

private:
  bool init_ = false;
  unsigned long last_time_;
  int read_interval_ms_ = 20;
  int pressed_state_ = HIGH;
  int pin_;
  int last_digital_read_;
  int long_press_ms_ = 2000;

  State state_ = State::nothing;

  struct {
    unsigned long time;
    bool eventOccured;
  } rising_, falling_;
};

#endif