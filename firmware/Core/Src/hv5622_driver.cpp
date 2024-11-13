// hv5622_driver.cpp
#include "hv5622_driver.h"

#include <cassert>

namespace {
static constexpr uint8_t BITS_PER_BYTE = 8;
static constexpr uint8_t BYTES_PER_WORD = 4;
static constexpr uint8_t BYTE_MASK = 0xFF;

static constexpr uint8_t BYTE3_SHIFT = BITS_PER_BYTE * 3;
static constexpr uint8_t BYTE2_SHIFT = BITS_PER_BYTE * 2;
static constexpr uint8_t BYTE1_SHIFT = BITS_PER_BYTE * 1;
static constexpr uint8_t BYTE0_SHIFT = 0;
}  // namespace

Hv5622_driver::Hv5622_driver(SPI_HandleTypeDef* hspi,
                             GPIO_TypeDef* blanking_n_port,
                             uint16_t blanking_n_pin,
                             GPIO_TypeDef* polarity_n_port,
                             uint16_t polarity_n_pin,
                             uint8_t num_drivers)
    : hspi_(hspi),
      blanking_n_port_(blanking_n_port),
      blanking_n_pin_(blanking_n_pin),
      polarity_n_port_(polarity_n_port),
      polarity_n_pin_(polarity_n_pin),
      num_drivers_(num_drivers) {
  // Start with blanking active (low) so everything is off
  blank_outputs(true);
  invert_output_polarity(false);
}

void Hv5622_driver::write_data(const uint32_t* data, uint8_t num_words) {
  assert(num_words == num_drivers_ &&
         "Number of words must match number of drivers!");

  // Data is shifted from the Shift register to the latches on logic input high.
  // Hold the latch pin (also chip select) low to load up the shift registers
  // Rising edge on latch transfers contents of shift register to the outputs
  // SPI periph will do this automatically

  // Send data for each driver
  for (int i = 0; i < num_drivers_; i++) {
    uint32_t word = data[i];

    // SPI Periph set to MSB so this will shift out starting with MSB
    // e.g. if sending a word with only MSB set high - HVOUT32 will be high and
    // all others low It's nice since the data words bits are mapped directly to
    // the (pin_name - 1) i.e bit0  -> HVOUT1 bit15 -> HVOUT16 bit31 -> HVOUT32
    uint8_t bytes[BYTES_PER_WORD] = {
        static_cast<uint8_t>((word >> BYTE3_SHIFT) & BYTE_MASK),  // MSB
        static_cast<uint8_t>((word >> BYTE2_SHIFT) & BYTE_MASK),
        static_cast<uint8_t>((word >> BYTE1_SHIFT) & BYTE_MASK),
        static_cast<uint8_t>((word >> BYTE0_SHIFT) & BYTE_MASK)};  // LSB

    HAL_SPI_Transmit(hspi_, bytes, BYTES_PER_WORD, HAL_MAX_DELAY);
  }
}

void Hv5622_driver::blank_outputs(bool state) {
  if (state) {
    HAL_GPIO_WritePin(blanking_n_port_, blanking_n_pin_, GPIO_PIN_RESET);
  } else {
    HAL_GPIO_WritePin(blanking_n_port_, blanking_n_pin_, GPIO_PIN_SET);
  }
}

void Hv5622_driver::invert_output_polarity(bool state) {
  // polarity_n low inverts all outputs (keep high for normal operation)
  if (state) {
    HAL_GPIO_WritePin(polarity_n_port_, polarity_n_pin_, GPIO_PIN_RESET);
  } else {
    HAL_GPIO_WritePin(polarity_n_port_, polarity_n_pin_, GPIO_PIN_SET);
  }
}

void Hv5622_driver::dimming(uint8_t level) {}