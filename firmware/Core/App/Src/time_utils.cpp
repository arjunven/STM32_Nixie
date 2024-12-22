// time_utils.cpp

#include "time_utils.hh"

namespace {

static constexpr uint8_t HOURS_TENS_INDEX = 0;
static constexpr uint8_t HOURS_ONES_INDEX = 1;
static constexpr uint8_t MINUTES_TENS_INDEX = 2;
static constexpr uint8_t MINUTES_ONES_INDEX = 3;
static constexpr uint8_t SECONDS_TENS_INDEX = 4;
static constexpr uint8_t SECONDS_ONES_INDEX = 5;

}  // namespace

namespace time_utils {

std::array<uint8_t, Nixie_display::NUM_TUBES> rtc_bcd_time_display_digits(
    RTC_TimeTypeDef time) {
  std::array<uint8_t, Nixie_display::NUM_TUBES> digits;

  // Extract hours, minutes, seconds
  uint8_t hours = time.Hours;
  uint8_t minutes = time.Minutes;
  uint8_t seconds = time.Seconds;

  digits[HOURS_TENS_INDEX] = (hours >> 4) & 0xF;
  digits[HOURS_ONES_INDEX] = hours & 0xF;

  digits[MINUTES_TENS_INDEX] = (minutes >> 4) & 0xF;
  digits[MINUTES_ONES_INDEX] = minutes & 0xF;

  digits[SECONDS_TENS_INDEX] = (seconds >> 4) & 0xF;
  digits[SECONDS_ONES_INDEX] = seconds & 0xF;

  return digits;
}

uint8_t bcd_to_binary(uint8_t bcd) {
  uint8_t tens = (bcd >> 4) * 10;
  uint8_t ones = bcd & 0xF;
  return tens + ones;
}

uint8_t binary_to_bcd(uint8_t binary) {
  uint8_t tens = binary / 10;
  uint8_t ones = binary % 10;
  return (tens << 4) | ones;
}

}  // namespace time_utils
