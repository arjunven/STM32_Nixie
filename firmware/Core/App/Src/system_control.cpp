#include "system_control.hh"

namespace system_control {
// TODO: add analog voltage check in system control

static constexpr uint16_t DELAY_ILIM = 100;
static constexpr uint16_t DELAY_12V = 100;
static constexpr uint16_t DELAY_180V = 100;

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

bool power_up() {
  // Increase the current limit of the input load switch
  HAL_GPIO_WritePin(SET_ILIM_GPIO_Port, SET_ILIM_Pin, GPIO_PIN_SET);
  HAL_Delay(DELAY_ILIM);

  // Turn on 12V rail
  enable_12v();
  HAL_Delay(DELAY_12V);  // Wait for rail to stabilize
  // TODO: read 12V rail voltage and check it looks good

  enable_180v();
  HAL_Delay(DELAY_180V);
  if (!is_180v_power_good) {
    return false;
  }

  return true;
}
}  // namespace system_control
