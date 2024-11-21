// nixie_display.h
#ifndef NIXIE_DISPLAY_H
#define NIXIE_DISPLAY_H

#include <array>

#include "hv5622_driver.h"

class Nixie_display {
 public:
  explicit Nixie_display(Hv5622_driver& hv_driver);

  static constexpr uint8_t NUM_DRIVERS = 2;
  static constexpr uint8_t NUM_TUBES = 6;

  /** @brief Turn off the display*/
  void disable();

  /** @brief Turn on the display */
  void enable();

  /** @brief Write a single 0-9 digit for a given tube position 0-7 */
  void set_digit(uint8_t tube_position, uint8_t digit);

  /** @brief Sets the whole display with the contents of the 6 elements of the
   * digits array. */
  void set_display(const std::array<uint8_t, NUM_TUBES>& digits);

  /** @brief Control the dots */
  void set_colon(bool left_on, bool right_on);

 private:
  Hv5622_driver& hv_driver_;
};

#endif