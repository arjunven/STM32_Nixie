// hv5622_driver.cpp
#include "hv5622_driver.h"

Hv5622_driver::Hv5622_driver(int data_pin,
                             int clock_pin,
                             int latch_pin,
                             int blanking_pin,
                             int polarity_pin)
    : data_pin_(data_pin),
      clock_pin_(clock_pin),
      latch_pin_(latch_pin),
      blanking_pin_(blanking_pin),
      polarity_pin_(polarity_pin)
{
    // setup gpio?

}