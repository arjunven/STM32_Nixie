// time_lord.cpp

#include "time_lord.hh"

namespace {
static constexpr uint8_t NIBBLE_MASK = 0xF;
static constexpr uint8_t BITS_PER_NIBBLE = 4;

static constexpr uint8_t HOURS_TENS_INDEX = 0;
static constexpr uint8_t HOURS_ONES_INDEX = 1;
static constexpr uint8_t MINUTES_TENS_INDEX = 2;
static constexpr uint8_t MINUTES_ONES_INDEX = 3;
static constexpr uint8_t SECONDS_TENS_INDEX = 4;
static constexpr uint8_t SECONDS_ONES_INDEX = 5;

// TODO: add slot machine roll over every hours to prevent cathode poisoning

}  // namespace

Time_lord::Time_lord(Nixie_display& display,
                     RTC_HandleTypeDef* hrtc,
                     RTC_TimeTypeDef initial_time)
    : display_(display), hrtc_(hrtc), time_(initial_time) {
  // Set initial time
  HAL_RTC_SetTime(hrtc_, &time_, RTC_FORMAT_BCD);

  // Start with blank display and then enable it
  display.disable();
  display.set_blank_digits();
  display.enable();
}

bool Time_lord::update_display() {
  HAL_StatusTypeDef status = HAL_RTC_GetTime(hrtc_, &time_, RTC_FORMAT_BCD);
  bool display_status;

  if (status != HAL_OK) {
    return false;
  }

  // Only update display if the time has changed since last check
  if (time_.Seconds != previous_time_.Seconds ||
      time_.Minutes != previous_time_.Minutes ||
      time_.Hours != previous_time_.Hours) {
    auto digits = bcd_time_to_display_array(time_);

    display_status = display_.set_display(digits);

    previous_time_ = time_;
    return display_status;
  }

  return true;  // No update needed (not an error condition)
}

std::array<uint8_t, Nixie_display::NUM_TUBES>
Time_lord::bcd_time_to_display_array(RTC_TimeTypeDef time) {
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