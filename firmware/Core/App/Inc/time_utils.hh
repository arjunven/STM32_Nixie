// time_utils.hh

#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include <array>

#include "nixie_display.hh"

namespace time_utils {

/** @brief Convert the HAL RTC Time representation to the array required to
 * set the display */
std::array<uint8_t, Nixie_display::NUM_TUBES> rtc_bcd_time_display_digits(
    RTC_TimeTypeDef time);

}  // namespace time_utils

#endif