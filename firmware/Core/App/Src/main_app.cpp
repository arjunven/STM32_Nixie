#include "main_app.hh"

#include "adc.h"
#include "gpio.h"
#include "hv5622_driver.hh"
#include "main.h"
#include "nixie_display.hh"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"

// Using the seperate main_app because CubeMX code generation will keep making a
// new main.c and clobbers the main.cpp. Instead this main_app gets called in
// main.c so CubeMX can happily keep generating code.

uint16_t LED_DELAY = 1000;  // ms
uint8_t TUBE_S2 = 5;
uint8_t TUBE_S1 = 4;
uint8_t TUBE_H2 = 3;

int main_app() {
  /* Initialization */
  // TODO: Check pin states on startup
  // TODO: Set pin pulls
  HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(SPI_nCS_nLE_GPIO_Port, SPI_nCS_nLE_Pin, GPIO_PIN_SET);

   HAL_Delay(1000);

  HAL_GPIO_WritePin(SET_ILIM_GPIO_Port, SET_ILIM_Pin, GPIO_PIN_SET);
  HAL_Delay(100);
  HAL_GPIO_WritePin(EN_12V_GPIO_Port, EN_12V_Pin, GPIO_PIN_SET);
  HAL_Delay(100);

  // TODO: add a power sequenceer

  // Initialize HV5622
  static Hv5622_driver hv_driver(&hspi1,
                                 SPI_nCS_nLE_GPIO_Port,
                                 SPI_nCS_nLE_Pin,
                                 PWM_nBL_GPIO_Port,
                                 PWM_nBL_Pin,
                                 nPOL_GPIO_Port,
                                 nPOL_Pin,
                                 Nixie_display::NUM_DRIVERS);

  // Initialize display
  static Nixie_display display(hv_driver);
  display.disable();

  std::array<uint8_t, Nixie_display::NUM_TUBES> numbers = {0, 0, 0, 0, 0, 0};

  HAL_GPIO_WritePin(EN_180V_GPIO_Port, EN_180V_Pin, GPIO_PIN_SET);
  HAL_Delay(100);
  display.enable();

  for (int i = 0; i <= 10; i++) {
    for (uint8_t time = 0; time <= Nixie_display::MAX_DIGIT; time++) {
      numbers[TUBE_H2] = time;
      numbers[TUBE_S1] = time;
      numbers[TUBE_S2] = time;
      display.set_display(numbers);
      HAL_Delay(100);
    }
  }

  HAL_Delay(1000);

  HAL_GPIO_WritePin(EN_180V_GPIO_Port, EN_180V_Pin, GPIO_PIN_RESET);

  while (1) {
    /* Super loop */
    // HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
    // HAL_Delay(LED_DELAY);
  }
}
