// nixie_display.h
#ifndef NIXIE_DISPLAY_H
#define NIXIE_DISPLAY_H

#include "hv5622_driver.h"

class Nixie_display {
 public:
  Nixie_display(Hv5622_driver& hv_driver);

  /** @brief Write a single 0-9 digit for a given tube position 0-7 */
  void set_digit(uint8_t tube_position, uint8_t digit);

  void set_display(); // TODO: think about datatype to hold the values for the display

  /** @brief Control the dots */
  void set_colon(bool left_on, bool right_on);
  
  /** @brief Turn off the display */
  void clear();

private:
 Hv5622_driver& hv_driver_;
};

#endif