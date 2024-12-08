// nixie_display.hh

#ifndef NIXIE_DISPLAY_H
#define NIXIE_DISPLAY_H

#include <array>

#include "hv5622_driver.hh"

class Nixie_display {
 public:
  explicit Nixie_display(Hv5622_driver& hv_driver);

  static constexpr uint8_t NUM_DRIVERS = 2;
  static constexpr uint8_t NUM_TUBES = 6;
  static constexpr uint8_t MAX_DIGIT = 9;
  static constexpr uint8_t BLANK_DIGIT = 0xFF;

  /** @brief Turn off the display*/
  void disable();

  /** @brief Turn on the display */
  void enable();

  // test

  // test

  /** @brief Write a single digit for a given tube position
   * @param tube_position Position of the nixie tube (0-5):
   *                     - 0: Hours tens
   *                     - 1: Hours ones
   *                     - 2: Minutes tens
   *                     - 3: Minutes ones
   *                     - 4: Seconds tens
   *                     - 5: Seconds ones
   * @param digit Value to display:
   *              - 0-9: Display the digit
   *              - 0xFF: Blank (all cathodes off)
   * @return true if successful, false on error
   */
  bool set_digit(uint8_t tube_position, uint8_t digit);

  /** @brief Sets all nixie tubes with the provided digit values
   * @param digits Array of values for each tube position:
   *               - 0-9: Display the digit
   *               - 0xFF: Blank (all cathodes off)
   *               Array index maps to tube position:
   *               [0] Hours tens
   *               [1] Hours ones
   *               [2] Minutes tens
   *               [3] Minutes ones
   *               [4] Seconds tens
   *               [5] Seconds ones
   * @return true if successful, false on error
   */
  bool set_display(const std::array<uint8_t, NUM_TUBES>& digits);

  /** @brief Control the dots */
  bool set_colon(bool left_on, bool right_on);

  // TODO: Dimming function

 private:
  Hv5622_driver& hv_driver_;
};

#endif