// hv5622_driver.h

#ifndef HV5622_DRIVER_H
#define HV5622_DRIVER_H

#include <cstdint>

#include "gpio.h"
#include "spi.h"

/**
 * @brief Driver for the HV5622 high-voltage shift register
 *
 * Handles SPI communication and control signals for cascaded HV5622 chips.
 */
class Hv5622_driver {
 public:
  /**
   * @brief Constructor for HV5622 driver
   * @param hspi SPI handle
   * @param blanking_n_port GPIO port for blanking
   * @param blanking_n_pin GPIO pin for blanking
   * @param polarity_n_port GPIO port for polarity
   * @param polarity_n_pin GPIO pin for polarity
   * @param num_drivers Number of cascaded chips
   */
  Hv5622_driver(SPI_HandleTypeDef* hspi,
                GPIO_TypeDef* blanking_n_port,
                uint16_t blanking_n_pin,
                GPIO_TypeDef* polarity_n_port,
                uint16_t polarity_n_pin,
                uint8_t num_drivers);

  /**
   * @brief Writes data to shift registers
   * @param data Array of 32-bit words
   * @param num_words Must match num_drivers
   */
  void write_data(const uint32_t* data, uint8_t num_words);

  /** @brief Controls output blanking (true = blank) */
  void blank_outputs(bool state);

  /** @brief Controls output polarity inversion (true = invert) */
  void invert_output_polarity(bool state);

  /** @brief Sets PWM dimming level (0-255) */
  void dimming(uint8_t level);

 private:
  static constexpr uint8_t BITS_PER_BYTE = 8;
  static constexpr uint8_t BYTES_PER_WORD = 4;
  static constexpr uint8_t BYTE_MASK = 0xFF;

  static constexpr uint8_t BYTE3_SHIFT = BITS_PER_BYTE * 3;
  static constexpr uint8_t BYTE2_SHIFT = BITS_PER_BYTE * 2;
  static constexpr uint8_t BYTE1_SHIFT = BITS_PER_BYTE * 1;
  static constexpr uint8_t BYTE0_SHIFT = 0;

  SPI_HandleTypeDef* hspi_;
  GPIO_TypeDef* blanking_n_port_;
  uint16_t blanking_n_pin_;
  GPIO_TypeDef* polarity_n_port_;
  uint16_t polarity_n_pin_;
  uint8_t num_drivers_;
};

#endif