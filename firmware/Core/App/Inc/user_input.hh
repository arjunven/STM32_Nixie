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
  Button_state get_button_state();

  /** @brief Returns how much the encoder has moved since last update with a
   * singed int8 */
  int8_t get_encoder_movement();

 private:
  TIM_HandleTypeDef* htim_;
  GPIO_TypeDef* button_port_;
  uint16_t button_pin_;
  bool button_input_;
  uint16_t current_encoder_count_;
  uint16_t last_encoder_count_;
  int8_t encoder_clicks_difference_;
};

#endif