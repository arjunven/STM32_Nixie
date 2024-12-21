// time_lord.hh

#ifndef TIME_LORD_H
#define TIME_LORD_H

#include <array>

#include "nixie_display.hh"
#include "rtc.h"

class Time_lord {
 public:
  Time_lord(Nixie_display& display,
            RTC_HandleTypeDef* hrtc,
            RTC_TimeTypeDef initial_time);

  /** @brief Gets time from RTC and updates the display to the current time  */
  bool update();

  /** @brief Sets the current time */
  bool set_time(RTC_TimeTypeDef time_to_set);

 private:
  Nixie_display& display_;
  RTC_HandleTypeDef* hrtc_;
  RTC_TimeTypeDef time_;

  /** @brief Convert the HAL RTC Time representation to the array required to
   * set the display */
  std::array<uint8_t, Nixie_display::NUM_TUBES> bcd_time_to_display_array(
      RTC_TimeTypeDef time);
};

#endif