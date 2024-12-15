// user_input.cpp

#include "user_input.hh"

namespace {
static constexpr uint8_t ENCODER_COUNTS_PER_CLICK = 4;
}  // namespace

User_input::User_input(TIM_HandleTypeDef* htim,
                       GPIO_TypeDef* button_port,
                       uint16_t button_pin)
    : htim_(htim), button_port_(button_port), button_pin_(button_pin) {
  HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
}

void User_input::update() {
  button_input_ =
      (HAL_GPIO_ReadPin(button_port_, button_pin_) == GPIO_PIN_RESET);

  last_encoder_count_ = current_encoder_count_;
  current_encoder_count_ = __HAL_TIM_GET_COUNTER(htim_);
}

int8_t User_input::get_encoder_movement() {
  return static_cast<int8_t>((current_encoder_count_ - last_encoder_count_) /
                             ENCODER_COUNTS_PER_CLICK);
}