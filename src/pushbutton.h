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

  PushButton(int pin, int pressed_state = HIGH, int read_cycle_ms = 20);
  void update(void);
  State pressed(void);

private:
  unsigned long last_time_;
  int read_cycle_ms_;
  int pressed_state_;
  int pin_;
  int last_digital_read_;

  State state_ = State::nothing;

  struct {
    unsigned long time;
    bool eventOccured;
  } rising_, falling_;
};

#endif