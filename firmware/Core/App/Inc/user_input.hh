// user_input.hh

#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "tim.h"

class User_input {
 public:
  User_input(TIM_HandleTypeDef* htim,
             GPIO_TypeDef* button_port,
             uint16_t button_pin);

  enum class Button_state { NONE, SHORT_PRESS, LONG_PRESS };

  /** Updates the current button input of the button and the encoder count. */
  void update();

  /** @brief Returns buttons state based on state changes since last update */
  Button_state get_button_state() const;

  /** @brief Returns how much the encoder has moved since last update with a
   * singed int8 */
  int8_t get_encoder_movement() const;

 private:
  TIM_HandleTypeDef* htim_;
  GPIO_TypeDef* button_port_;
  uint16_t button_pin_;

  static constexpr uint32_t LONG_PRESS_TIME_MS = 750;
  static constexpr uint32_t SHORT_PRESS_TIME_MS = 50;

  // TODO: should I have initialized values for these?

  bool current_button_pressed_;
  bool last_button_pressed_;
  uint32_t button_press_start_tick_;
  uint32_t time_pressed_;  // ms
  Button_state button_state_;

  uint16_t current_encoder_count_;
  uint16_t last_encoder_count_;
};

#endif