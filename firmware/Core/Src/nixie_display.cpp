#include "nixie_display.h"

#include <cassert>

#include "hv5622_driver.h"

namespace {
/** @brief Maps Nixie tube digits to 64 bit ints, based on layout of board */
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

static constexpr uint8_t MAX_POSITION = 5;
static constexpr uint8_t MAX_DIGIT = 9;
static constexpr uint8_t POSITION_MAPPING = 10;

static constexpr uint32_t WORD_MASK = 0xFFFFFFFF;
static constexpr uint8_t BITS_PER_WORD = 32;

static uint64_t get_digit_pattern(uint8_t position, uint8_t digit) {
  assert(position <= MAX_POSITION && "Tube position must be 0-5");
  assert(digit <= MAX_DIGIT && "Digits must be 0-9");

  return DIGIT_MAP[position * POSITION_MAPPING + digit];
}
}  // namespace

Nixie_display::Nixie_display(Hv5622_driver& hv_driver)
    : hv_driver_(hv_driver) {}

void Nixie_display::set_digit(uint8_t position, uint8_t digit) {
  assert(position <= MAX_POSITION && "Tube position must be 0-5");
  assert(digit <= MAX_DIGIT && "Digits must be 0-9");

  uint64_t digit_pattern = get_digit_pattern(position, digit);
  
  // Split digit pattern to array of 32 bit words
  uint32_t data[2];
  // TODO: how to store the fact that there are 2 drivers? Hardcode or set as a private variable of class?

  Nixie_display::hv_driver_.write_data(data, 2);
}