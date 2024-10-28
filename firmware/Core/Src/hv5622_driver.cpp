// hv5622_driver.cpp
#include "hv5622_driver.h"

#include <cassert>

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
  HAL_GPIO_WritePin(blanking_n_port_, blanking_n_pin_, GPIO_PIN_RESET);

  // polarity_n low inverts all outputs (keep high for normal operation)
  HAL_GPIO_WritePin(polarity_n_port_, polarity_n_pin_, GPIO_PIN_SET);
}

void Hv5622_driver::write_data(const uint32_t* data, uint8_t num_words) {
  assert(num_words == num_drivers_ &&
         "Number of words must match number of drivers!");

  
}