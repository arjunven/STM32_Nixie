// hv5622_driver.h

#ifndef HV5622_DRIVER_H
#define HV5622_DRIVER_H

#include <cstdint>

class Hv5622_driver
{
public:
    Hv5622_driver(
        int data_pin,
        int clock_pin,
        int latch_pin,
        int blanking_pin,
        int polarity_pin);

    void clear_display();
    void set_digit(int position, int digit);

private:
    int data_pin_;
    int clock_pin_;
    int latch_pin_;
    int blanking_pin_;
    int polarity_pin_;

    void shift_out(uint32_t data);
};

#endif