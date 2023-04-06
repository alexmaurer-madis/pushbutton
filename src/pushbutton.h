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
#include <cstdint>

class PushButton {

public:
  enum class State { nothing, shortPress, longPress };

  PushButton(void);
  PushButton(uint8_t pin, int pressed_state = HIGH,
             uint16_t long_press_ms = 2000, uint16_t read_cycle_ms = 20);

  void setPin(uint8_t pin, uint8_t mode = INPUT, int pressed_state = HIGH,
              uint16_t long_press_ms = 2000);

  void setReadInterval(uint16_t read_cycle_ms);
  uint16_t getReadInterval(void);

  void setLongPressDuration(uint16_t long_press_ms);
  uint16_t getLongPressDuration(void);

  void process(void);
  State getState(void);

private:
  bool init_ = false;
  uint16_t read_interval_ms_ = 20;
  uint16_t long_press_ms_ = 2000;
  uint8_t pin_;
  int pressed_state_ = HIGH;
  unsigned long last_time_;
  int last_digital_read_;
  State state_ = State::nothing;

  struct {
    unsigned long time;
    bool eventOccured;
  } rising_;
};

#endif