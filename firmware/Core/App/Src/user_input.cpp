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
  button_state_ = Button_state::NONE;
}

void User_input::update() {
  // Button state update
  last_button_pressed_ = current_button_pressed_;

  current_button_pressed_ =
      (HAL_GPIO_ReadPin(button_port_, button_pin_) == GPIO_PIN_RESET);

  if (current_button_pressed_) {
    // Button is held
    if (last_button_pressed_) {
      // Calculate how long it's been pressed for
      time_pressed_ = HAL_GetTick() - button_press_start_tick_;

      if (time_pressed_ > LONG_PRESS_TIME_MS) {
        button_state_ = Button_state::LONG_PRESS;
      }
    }

    // Button newly pressed
    else {
      // Just set the start tick for the next cycle
      button_press_start_tick_ = HAL_GetTick();
    }
  }

  // Short press is only registered on a short press and a release and we are
  // currently None state
  else if (last_button_pressed_ &&
           button_state_ == User_input::Button_state::NONE &&
           time_pressed_ > SHORT_PRESS_TIME_MS) {
    button_state_ = Button_state::SHORT_PRESS;
  }

  // Button is not pressed
  else {
    // Reset button press timer
    button_state_ = Button_state::NONE;
  }

  // Encoder state update
  last_encoder_count_ = current_encoder_count_;
  current_encoder_count_ = __HAL_TIM_GET_COUNTER(htim_);
}

int8_t User_input::get_encoder_movement() const {
  return static_cast<int8_t>((current_encoder_count_ - last_encoder_count_) /
                             ENCODER_COUNTS_PER_CLICK);
}

User_input::Button_state User_input::get_button_state() const {
  return button_state_;
}