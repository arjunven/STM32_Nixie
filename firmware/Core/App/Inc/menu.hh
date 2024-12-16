// menu.hh

#ifndef MENU_H
#define MENU_H

#include "time_lord.hh"
#include "user_input.hh"

class Menu {
 public:
  explicit Menu(Time_lord& chronos);

  /** Updates the menu state based on the  */
  void update(const User_input& input);

 private:
  Time_lord& chronos_;

  enum class State {
    NORMAL,
    SETTING_TIME,
    SETTING_DATE,
    SETTING_DIMMING,
  };

  enum class Time_field { HOURS, MINUTES };

  State current_state_ = State::NORMAL;
  Time_field current_time_field_ = Time_field::HOURS;
  uint32_t last_activity_time_ = 0;

  static constexpr uint32_t TIMOUT_MS = 10000;  // 10s timeout
};

#endif