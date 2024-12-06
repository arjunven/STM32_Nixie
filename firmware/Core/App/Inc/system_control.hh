// system_control.hh

#ifndef SYSTEM_CONTROL_H
#define SYSTEM_CONTROL_H

namespace system_control {
bool power_up();
void enable_180v();
void enable_12v();

bool is_180v_power_good();

void power_down();
void disable_180v();
void disable_12v();

void gpio_init();
void enable_fault_led();
void disable_fault_led();
void enable_heartbeat_led();
void disable_heartbeat_led();
void enable_status_led();
void disable_status_led();
}  // namespace system_control

#endif
