// nixie_display.cpp

#include "nixie_display.hh"

#include <algorithm>
#include <cassert>
// TODO: get rid of the asserts

namespace {
/** @brief Maps Nixie tube digits to 64 bit ints, based on layout of board.
 *
 * Mapped so that MSB corresponds to highest output of second driver i.e.
 * MSB high would set HVOUT32 of driver 2 high and LSB high would set HVOUT1 of
 * first driver high.
 */
static constexpr uint64_t DIGIT_MAP[60] = {
    // Tube 0 = Hours 1
    0x0000020000000000ULL,  // 0
    0x0000000100000000ULL,  // 1
    0x0000000200000000ULL,  // 2
    0x0000000400000000ULL,  // 3
    0x0000000800000000ULL,  // 4
    0x0000001000000000ULL,  // 5
    0x0000002000000000ULL,  // 6
    0x0000004000000000ULL,  // 7
    0x0000008000000000ULL,  // 8
    0x0000010000000000ULL,  // 9

    // Tube 1 = Hours 2
    0x0010000000000000ULL,  // 0
    0x0000080000000000ULL,  // 1
    0x0000100000000000ULL,  // 2
    0x0000200000000000ULL,  // 3
    0x0000400000000000ULL,  // 4
    0x0000800000000000ULL,  // 5
    0x0001000000000000ULL,  // 6
    0x0002000000000000ULL,  // 7
    0x0004000000000000ULL,  // 8
    0x0008000000000000ULL,  // 9

    // Tube 2 = Minutes 1
    0x8000000000000000ULL,  // 0
    0x0040000000000000ULL,  // 1
    0x0080000000000000ULL,  // 2
    0x0100000000000000ULL,  // 3
    0x0200000000000000ULL,  // 4
    0x0400000000000000ULL,  // 5
    0x0800000000000000ULL,  // 6
    0x1000000000000000ULL,  // 7
    0x2000000000000000ULL,  // 8
    0x4000000000000000ULL,  // 9

    // Tube 3 = Minutes 2
    0x0000000000000200ULL,  // 0
    0x0000000000000001ULL,  // 1
    0x0000000000000002ULL,  // 2
    0x0000000000000004ULL,  // 3
    0x0000000000000008ULL,  // 4
    0x0000000000000010ULL,  // 5
    0x0000000000000020ULL,  // 6
    0x0000000000000040ULL,  // 7
    0x0000000000000080ULL,  // 8
    0x0000000000000100ULL,  // 9

    // Tube 4 = Seconds 1
    0x0000000000200000ULL,  // 0
    0x0000000000001000ULL,  // 1
    0x0000000000002000ULL,  // 2
    0x0000000000004000ULL,  // 3
    0x0000000000008000ULL,  // 4
    0x0000000000010000ULL,  // 5
    0x0000000000020000ULL,  // 6
    0x0000000000040000ULL,  // 7
    0x0000000000080000ULL,  // 8
    0x0000000000100000ULL,  // 9

    // Tube 5 = Seconds 2
    0x0000000080000000ULL,  // 0
    0x0000000000400000ULL,  // 1
    0x0000000000800000ULL,  // 2
    0x0000000001000000ULL,  // 3
    0x0000000002000000ULL,  // 4
    0x0000000004000000ULL,  // 5
    0x0000000008000000ULL,  // 6
    0x0000000010000000ULL,  // 7
    0x0000000020000000ULL,  // 8
    0x0000000040000000ULL,  // 9
};

static constexpr uint64_t BLANK_DIGIT_PATTERN = 0;

static constexpr uint8_t POSITION_MAPPING = 10;

static constexpr uint32_t WORD_MASK = 0xFFFFFFFF;
static constexpr uint8_t BITS_PER_WORD = 32;

static constexpr uint32_t SLOT_MACHINE_DELAY = 100;  // ms

// Get the digit pattern from the digit map using the tube position and the
// digit number
static uint64_t get_digit_pattern(uint8_t position, uint8_t digit) {
  assert(position < Nixie_display::NUM_TUBES && "Tube position must be [0,5]");
  assert((digit <= Nixie_display::MAX_DIGIT ||
          digit == Nixie_display::BLANK_DIGIT) &&
         "Digits must be in range [0,9]");

  if (digit == Nixie_display::BLANK_DIGIT) {
    return BLANK_DIGIT_PATTERN;
  } else {
    return DIGIT_MAP[position * POSITION_MAPPING + digit];
  }
}

// Split the 64bit digit pattern into a 2 element array of 32bit words for the
// driver
static std::array<uint32_t, Nixie_display::NUM_DRIVERS> split_digit_pattern(
    uint64_t digit_pattern) {
  return {static_cast<uint32_t>(digit_pattern >> BITS_PER_WORD),  // MSB
          static_cast<uint32_t>(digit_pattern & WORD_MASK)};      // LSB
}

}  // namespace

Nixie_display::Nixie_display(Hv5622_driver& hv_driver) : hv_driver_(hv_driver) {
  disable();
}

void Nixie_display::disable() { hv_driver_.blank_outputs(true); }

void Nixie_display::enable() { hv_driver_.blank_outputs(false); }

bool Nixie_display::set_digit(uint8_t position, uint8_t digit) {
  if (position >= NUM_TUBES) {
    return false;
  }

  if (digit > MAX_DIGIT && digit != BLANK_DIGIT) {
    return false;
  }

  uint64_t digit_pattern = get_digit_pattern(position, digit);

  std::array<uint32_t, NUM_DRIVERS> data = split_digit_pattern(digit_pattern);

  return hv_driver_.write_data(data.data(), NUM_DRIVERS);
}

bool Nixie_display::set_current_digits(std::array<uint8_t, NUM_TUBES> digits) {
  for (uint8_t i = 0; i < NUM_TUBES; i++) {
    if (digits[i] > MAX_DIGIT && digits[i] != BLANK_DIGIT) {
      return false;
    }
  }

  current_digits_ = digits;
  return true;
}

bool Nixie_display::set_display(const std::array<uint8_t, NUM_TUBES>& digits) {
  uint64_t digit_pattern = 0;

  // Build the full digit pattern by OR'ing all the individual digit patterns
  // together and check the the digits are valid
  for (uint8_t i = 0; i < NUM_TUBES; i++) {
    if (digits[i] > MAX_DIGIT && digits[i] != BLANK_DIGIT) {
      return false;
    }
    digit_pattern = digit_pattern | get_digit_pattern(i, digits[i]);
  }

  // Update internal state
  current_digits_ = digits;

  std::array<uint32_t, NUM_DRIVERS> data = split_digit_pattern(digit_pattern);

  return hv_driver_.write_data(data.data(), NUM_DRIVERS);
}

bool Nixie_display::set_display(uint8_t digit) {
  if (digit > MAX_DIGIT && digit != BLANK_DIGIT) {
    return false;
  }

  std::array<uint8_t, NUM_TUBES> digits;
  digits.fill(digit);

  return set_display(digits);
}

bool Nixie_display::set_blank_digits() { return set_display(BLANK_DIGIT); }

bool Nixie_display::set_blinking_positions(
    const std::array<bool, NUM_TUBES> positions) {
  blinking_positions_ = positions;
  return true;
}

void Nixie_display::stop_blinking() {
  // Set all to false to indicate no blinking
  std::fill(blinking_positions_.begin(), blinking_positions_.end(), false);
}

void Nixie_display::update() {
  // Check if any positions should blink
  bool any_blinks = std::any_of(blinking_positions_.begin(),
                                blinking_positions_.end(),
                                [](bool x) { return x; });

  if (any_blinks) {
    // Check if it's time to toggle the blink state
    if ((HAL_GetTick() - last_blink_time_) > BLINK_INTERVAL) {
      blink_state_ = !blink_state_;
      last_blink_time_ = HAL_GetTick();
    }

    // Blank the digit if it's blinking time
    if (!blink_state_) {
      auto blink_digits = current_digits_;

      // Blank the digits we want to blink
      for (uint8_t i = 0; i < NUM_TUBES; i++) {
        if (blinking_positions_[i]) {
          blink_digits[i] = BLANK_DIGIT;
        }
      }

      set_display(blink_digits);
    }

    else {
      set_display(current_digits_);
    }
  }

  else {
    set_display(current_digits_);
  }
}

void Nixie_display::slot_machine() {
  for (uint8_t i = 0; i <= MAX_DIGIT; i++) {
    set_display(i);
    HAL_Delay(SLOT_MACHINE_DELAY);
  }
}