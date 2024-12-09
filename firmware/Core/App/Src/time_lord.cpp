// time_lord.cpp

#include "time_lord.hh"

Time_lord::Time_lord(Nixie_display& display, RTC_HandleTypeDef* hrtc)
    : display_(display), hrtc_(hrtc) {
  // Start with blank display and then enable it
  display.disable();
  display.set_blank_digits();
  display.enable();
}
