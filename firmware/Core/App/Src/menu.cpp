// menu.cpp

#include "menu.hh"

#include "time_utils.hh"
#include "user_input.hh"

namespace {
static constexpr std::array<bool, Nixie_display::NUM_TUBES> HOUR_BLINK_POS = {
    true, true, false, false, false, false};

static constexpr std::array<bool, Nixie_display::NUM_TUBES> MINUTE_BLINK_POS = {
    false, false, true, true, false, false};

}  // namespace

Menu::Menu(Time_lord& chronos, Nixie_display& display)
    : chronos_(chronos), display_(display) {}

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
  // Always start by setting hours
  current_time_field_ = Menu::Time_field::HOURS;

  // Get inputs
  int8_t movement = input.get_encoder_movement();
  User_input::Button_state button_state = input.get_button_state();

  // Start the draft time at the current time
  draft_time_ = chronos_.get_time();

  switch (current_time_field_) {
    case Menu::Time_field::HOURS: {
      // Make the hours blink
      display_.set_blinking_positions(HOUR_BLINK_POS);

      // Adjust the hours
      adjust_hours(movement);

      // Display what you've adjusted
      auto digits = time_utils::rtc_bcd_time_display_digits(draft_time_);
      display_.set_current_digits(digits);

      // Short press moves to minutes
      if (button_state == User_input::Button_state::SHORT_PRESS) {
        current_time_field_ = Menu::Time_field::MINUTES;
      }
      break;
    }

    case Menu::Time_field::MINUTES: {
      // Make the minutes blink
      display_.set_blinking_positions(MINUTE_BLINK_POS);

      // Adjust the minutes
      adjust_minutes(movement);

      // Display what you've adjusted
      auto digits = time_utils::rtc_bcd_time_display_digits(draft_time_);
      display_.set_current_digits(digits);

      // Short press actually sets time_lords time and exits the menu
      chronos_.set_time(draft_time_);
      current_state_ = Menu::State::NORMAL;
      // TODO: long press exits menu? and short press continues to set date?

      break;
    }
  }

  // For now, long press exits menu

  // Later: long button press goes to next menu item
  // Maybe make make a structure that orders the menu items and then have a next
  // menu item function that cycles to the next one?
}

void Menu::adjust_hours(int8_t change) {
  // Convert BCD hours to binary to add our change
  auto hours =
      static_cast<int8_t>(time_utils::bcd_to_binary(draft_time_.Hours));

  hours += change;

  // Handle positive roll over
  if (hours >= time_utils::HOURS_PER_DAY) {
    hours -= time_utils::HOURS_PER_DAY;
  }

  // Handle negative roll over
  if (hours < 0) {
    hours += time_utils::HOURS_PER_DAY;
  }

  // Store the changed hours
  draft_time_.Hours = time_utils::binary_to_bcd(static_cast<uint8_t>(hours));
}

void Menu::adjust_minutes(int8_t change) {
  // Convert BCD minutes to binarr so we can add the change
  auto minutes =
      static_cast<int8_t>(time_utils::bcd_to_binary(draft_time_.Minutes));

  minutes += change;

  // Handle positive roll over
  if (minutes >= time_utils::MINUTS_PER_HOUR) {
    minutes -= time_utils::MINUTS_PER_HOUR;
  }

  // Handle negative roll over
  if (minutes < 0) {
    minutes += time_utils::MINUTS_PER_HOUR;
  }

  // Store change minutes
  draft_time_.Minutes =
      time_utils::binary_to_bcd(static_cast<uint8_t>(minutes));
}