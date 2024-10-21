// hv5622_driver.cpp
#include "hv5622_driver.h"

Hv5622_driver::Hv5622_driver(SPI_HandleTypeDef *hspi,
                             GPIO_TypeDef *blanking_pin_port, uint16_t blanking_pin,
                             GPIO_TypeDef *polarity_pin_port, uint16_t polarity_pin)
    : hspi_(hspi),
      blanking_pin_port_(blanking_pin_port),
      blanking_pin_(blanking_pin),
      polarity_pin_port_(polarity_pin_port),
      polarity_pin_(polarity_pin)
{
  // setup gpio?
}