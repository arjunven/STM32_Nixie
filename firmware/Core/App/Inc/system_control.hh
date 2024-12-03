// system_control.hh

#ifndef SYSTEM_CONTROL_H
#define SYSTEM_CONTROL_H

#include "gpio.h"

namespace system_control {
bool power_up();
void enable_180v();
void enable_12v();

bool is_180v_power_good();

bool power_down();
void disable_180v();
void disable_12v();

void gpio_init();
}  // namespace system_control

#endif