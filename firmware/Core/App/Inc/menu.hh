// menu.hh

#ifndef MENU_H
#define MENU_H

#include "time_lord.hh"
#include "user_input.hh"

class Menu {
 public:
  explicit Menu(Time_lord& chronos, Nixie_display& display);

  /** Updates the menu state based on the state of the inputs  */
  void update(const User_input& input);

 private:
  Time_lord& chronos_;
  Nixie_display& display_;

  enum class State {
    NORMAL,
    SETTING_TIME,
    SETTING_DATE,
  };

  enum class Time_field { HOURS, MINUTES };

  State current_state_{State::NORMAL};
  Time_field current_time_field_{Time_field::HOURS};
  uint32_t last_activity_time_{0};
  RTC_TimeTypeDef draft_time_;

  static constexpr uint32_t TIMOUT_MS = 10000;  // 10s timeout

  void handle_normal_state(const User_input& input);
  void handle_setting_time(const User_input& input);
  void handle_setting_date(const User_input& input);
  void adjust_hours(int8_t change);
  void adjust_minutes(int8_t change);
};

#endif