#include "main_app.hh"
#include "nixie_display.hh"
#include "hv5622_driver.hh"

#include "adc.h"
#include "gpio.h"
#include "main.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"

// Using the seperate main_app because CubeMX code generation will keep making a
// new main.c and clobbers the main.cpp. Instead this main_app gets called in
// main.c so CubeMX can happily keep generating code.

uint16_t LED_DELAY = 1000; // ms
uint8_t SECONDS_2 = 5;

int main_app() {
  /* Initialization */
  // TODO: Check pin states on startup

  HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);

  HAL_GPIO_WritePin(SET_ILIM_GPIO_Port, SET_ILIM_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(EN_12V_GPIO_Port, EN_12V_Pin, GPIO_PIN_SET);

  // Initialize HV5622
  Hv5622_driver hv_driver(&hspi1,
                          PWM_nBL_GPIO_Port,
                          PWM_nBL_Pin,
                          nPOL_GPIO_Port,
                          nPOL_Pin,
                          Nixie_display::NUM_DRIVERS);

  // HAL_GPIO_WritePin(PWM_nBL_GPIO_Port, PWM_nBL_Pin, GPIO_PIN_RESET);
  // HAL_GPIO_WritePin(nPOL_GPIO_Port, nPOL_Pin, GPIO_PIN_RESET);

  // HAL_GPIO_WritePin(PWM_nBL_GPIO_Port, PWM_nBL_Pin, GPIO_PIN_SET);
  // HAL_GPIO_WritePin(nPOL_GPIO_Port, nPOL_Pin, GPIO_PIN_SET);

  // Initialize display
  Nixie_display display(hv_driver);

  // Turn off display to start

  // HAL_GPIO_WritePin(EN_180V_GPIO_Port, EN_180V_Pin, GPIO_PIN_SET);

  uint8_t time = 1;
  display.set_digit(SECONDS_2, time);
  display.enable();

  // HAL_Delay(1000);
  // HAL_GPIO_WritePin(EN_180V_GPIO_Port, EN_180V_Pin, GPIO_PIN_RESET);


  while (1) {
    /* Super loop */
    // HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
    // HAL_Delay(LED_DELAY);
  }
}