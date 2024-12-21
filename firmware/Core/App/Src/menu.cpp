// menu.cpp

#include "menu.hh"

#include "user_input.hh"

Menu::Menu(Time_lord& chronos) : chronos_(chronos) {}

void Menu::update(const User_input& input) {
  // First handle timeout check for all state except NORMAL
  if (current_state_ != State::NORMAL &&
      (HAL_GetTick() - last_activity_time_) > TIMOUT_MS) {
    current_state_ = State::NORMAL;
    return;
  }

  // Dispatch to appropriate state handler
  switch (current_state_) {
    case State::NORMAL:
      handle_normal_state(input);
      break;

    case State::SETTING_TIME:
      handle_setting_time(input);
      break;

    case State::SETTING_DATE:
      handle_setting_date(input);
      break;
  }
}

void Menu::handle_normal_state(const User_input& input) {
  // Do some dimming if the encoder movement is from his state
  int8_t movement = input.get_encoder_movement();
  User_input::Button_state button_state = input.get_button_state();

  // Short press is show date for some amount of time

  // Long press is going to time setting mode
  if (button_state == User_input::Button_state::LONG_PRESS) {
    current_state_ = Menu::State::SETTING_TIME;
    // TODO: replace this with a go to next menu item function? That way menu
    // item order can be handled with a single datastructure and order can be
    // easily rearragned if wanted
  }
}

void Menu::handle_setting_time(const User_input& input) {
  int8_t movement = input.get_encoder_movement();
  User_input::Button_state button_state = input.get_button_state();

  // Encoder movement increments the digit in the range of valid values (this
  // depends on which digit we're on)

  // Short button press, confirms current digit and goes to the next digit to
  // set time

  // long button press goes to next menu item
  // Maybe make make a structure that orders the menu items and then have a next
  // menu item function that cycles to the next one?
}