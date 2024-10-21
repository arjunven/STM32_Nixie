// hv5622_driver.h

#ifndef HV5622_DRIVER_H
#define HV5622_DRIVER_H

#include <cstdint>
#include "spi.h"
#include "gpio.h"

class Hv5622_driver
{
public:
    Hv5622_driver(
        SPI_HandleTypeDef *hspi,
        GPIO_TypeDef *blanking_pin_port, uint16_t blankin_ping,
        GPIO_TypeDef *polarity_pin_port, uint16_t polarity_pin);

    void clear_display();
    void set_digit(int position, int digit);

private:
    SPI_HandleTypeDef *hspi_;
    GPIO_TypeDef *blanking_pin_port_;
    uint16_t blanking_pin_;
    GPIO_TypeDef *polarity_pin_port_;
    uint16_t polarity_pin_;

    void shift_out(uint32_t data);
};

#endif