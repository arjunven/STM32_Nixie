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

  // Button stuff
  static constexpr uint32_t LONG_PRESS_TIME_MS = 750;
  static constexpr uint32_t SHORT_PRESS_TIME_MS = 50;

  void handle_button();

  bool current_button_pressed_{false};
  bool last_button_pressed_{false};
  uint32_t button_press_start_tick_{0};
  uint32_t time_pressed_{0};  // ms
  Button_state button_state_{Button_state::NONE};

  // Encoder stuff
  static constexpr uint32_t COUNT_ACCUMULATION_TIME_MS = 10;

  void handle_encoder();

  uint16_t current_encoder_count_{0};
  uint16_t last_encoder_count_{0};
  int8_t encoder_movement_{0};
};

#endif