// time_lord.cpp

#include "time_lord.hh"

#include "time_utils.hh"

Time_lord::Time_lord(Nixie_display& display, RTC_HandleTypeDef* hrtc)
    : display_(display), hrtc_(hrtc) {
  // Start with blank display and then enable it
  display.disable();
  display.set_blank_digits();
  display.enable();
}

bool Time_lord::update() {
  HAL_StatusTypeDef status = HAL_RTC_GetTime(hrtc_, &time_, RTC_FORMAT_BCD);
  bool display_status;

  if (status != HAL_OK) {
    return false;
  }

  // Every hour roll over play an slot machine animation to help prevent cathode
  // poisoning
  if (time_.Minutes == 0 && time_.Seconds == 0) {
    display_.slot_machine();
  }

  // Convert current time to digits and set display's internal state
  auto digits = time_utils::rtc_bcd_time_display_digits(time_);
  display_status = display_.set_current_digits(digits);

  return display_status;
}

bool Time_lord::set_time(RTC_TimeTypeDef time_to_set) {
  HAL_StatusTypeDef status =
      HAL_RTC_SetTime(hrtc_, &time_to_set, RTC_FORMAT_BCD);

  if (status == HAL_OK) {
    return true;
  } else {
    return false;
  }
}

RTC_TimeTypeDef Time_lord::get_time() { return time_; }