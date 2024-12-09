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
  bool update_display();

  // TODO: add a set time command

 private:
  Nixie_display& display_;
  RTC_HandleTypeDef* hrtc_;
  RTC_TimeTypeDef time_;

  /** @brief Poll RTC for current time */
  RTC_TimeTypeDef get_rtc_time();

  /** @brief Convert the HAL RTC Time representation to the array required to
   * set the display */
  std::array<uint8_t, Nixie_display::NUM_TUBES> time_to_display_array(
      RTC_TimeTypeDef time);
};

#endif