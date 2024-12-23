// time_lord.hh

#ifndef TIME_LORD_H
#define TIME_LORD_H

#include <array>

#include "nixie_display.hh"
#include "rtc.h"

class Time_lord {
 public:
  Time_lord(Nixie_display& display, RTC_HandleTypeDef* hrtc);

  /** @brief Gets time from RTC and updates the display to the current time  */
  bool update();

  /** @brief Sets the current time */
  bool set_time(RTC_TimeTypeDef time_to_set);

  /** @brief Returns the current time */
  RTC_TimeTypeDef get_time();

 private:
  Nixie_display& display_;
  RTC_HandleTypeDef* hrtc_;
  RTC_TimeTypeDef time_;  // Starts from 00:00:00
};

#endif