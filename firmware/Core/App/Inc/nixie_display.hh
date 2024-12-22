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
  bool set_digit(uint8_t position, uint8_t digit);

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

  /** @brief Write all blanks to the display */
  bool set_blank_digits();

  /** @brief Update the current digits field of the display
   *   @return false if inputs are not valid */
  bool set_current_digits(const std::array<uint8_t, NUM_TUBES> digits);

  /** @brief Used to update display if blinking is enabled or not. Does nothing
   * if blinking disabled */
  void update();

  /** @brief Control the dots */
  // bool set_colon(bool left_on, bool right_on);

  // TODO: Dimming function

  /** @brief Specify which digit to blink during the update command
   * @return True if blanking digit set successfully, false if position out of
   * range */
  bool set_blinking_positions(const std::array<bool, NUM_TUBES> positions);

  /** @brief Specify stop blinking for the update command */
  void stop_blinking();

 private:
  Hv5622_driver& hv_driver_;

  std::array<uint8_t, NUM_TUBES> current_digits_{0, 0, 0, 0, 0, 0};

  static constexpr uint32_t BLINK_INTERVAL = 200;

  // Used to enable blinking
  std::array<bool, NUM_TUBES> blinking_positions_{};
  // True is show digit, false is blank the digit
  bool blink_state_{true};
  uint32_t last_blink_time_{0};
};

#endif