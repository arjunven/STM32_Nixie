// time_utils.hh

#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include <array>

#include "nixie_display.hh"

namespace time_utils {

constexpr uint8_t HOURS_PER_DAY = 24;
constexpr uint8_t MINUTS_PER_HOUR = 60;

/** @brief Convert the HAL RTC Time representation to the array required to
 * set the display */
std::array<uint8_t, Nixie_display::NUM_TUBES> rtc_bcd_time_display_digits(
    RTC_TimeTypeDef time);

uint8_t bcd_to_binary(uint8_t bcd);

uint8_t binary_to_bcd(uint8_t binary);

}  // namespace time_utils

#endif