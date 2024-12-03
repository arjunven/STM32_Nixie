#include "system_control.hh"

namespace system_control {

void enable_180v() {
  HAL_GPIO_WritePin(EN_180V_GPIO_Port, EN_180V_Pin, GPIO_PIN_SET);
}

void disable_180v() {
  HAL_GPIO_WritePin(EN_180V_GPIO_Port, EN_180V_Pin, GPIO_PIN_RESET);
}

void enable_12v() {
  HAL_GPIO_WritePin(EN_12V_GPIO_Port, EN_12V_Pin, GPIO_PIN_SET);
}

void disable_12() {
  HAL_GPIO_WritePin(EN_12V_GPIO_Port, EN_12V_Pin, GPIO_PIN_RESET);
}

bool is_180v_power_good() {
  return HAL_GPIO_ReadPin(PG_180V_GPIO_Port, PG_180V_Pin) == GPIO_PIN_SET;
}
}  // namespace system_control
