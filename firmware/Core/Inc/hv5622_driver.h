// hv5622_driver.h

#ifndef HV5622_DRIVER_H
#define HV5622_DRIVER_H

#include <cstdint>

#include "gpio.h"
#include "spi.h"

class Hv5622_driver {
 public:
  Hv5622_driver(SPI_HandleTypeDef* hspi,
                GPIO_TypeDef* blanking_n_port,
                uint16_t blanking_n_pin,
                GPIO_TypeDef* polarity_n_port,
                uint16_t polarity_n_pin,
                uint8_t num_drivers);

  void write_data(const uint32_t* data, uint8_t num_words);

 private:
  SPI_HandleTypeDef* hspi_;
  GPIO_TypeDef* blanking_n_port_;
  uint16_t blanking_n_pin_;
  GPIO_TypeDef* polarity_n_port_;
  uint16_t polarity_n_pin_;
  uint8_t num_drivers_;
};

#endif