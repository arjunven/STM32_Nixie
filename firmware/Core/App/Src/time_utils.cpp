// time_utils.cpp

#include "time_utils.hh"

namespace {
static constexpr uint8_t NIBBLE_MASK = 0xF;
static constexpr uint8_t BITS_PER_NIBBLE = 4;

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

  digits[HOURS_TENS_INDEX] = (hours >> BITS_PER_NIBBLE) & NIBBLE_MASK;
  digits[HOURS_ONES_INDEX] = hours & NIBBLE_MASK;

  digits[MINUTES_TENS_INDEX] = (minutes >> BITS_PER_NIBBLE) & NIBBLE_MASK;
  digits[MINUTES_ONES_INDEX] = minutes & NIBBLE_MASK;

  digits[SECONDS_TENS_INDEX] = (seconds >> BITS_PER_NIBBLE) & NIBBLE_MASK;
  digits[SECONDS_ONES_INDEX] = seconds & NIBBLE_MASK;

  return digits;
}

}  // namespace time_utils
