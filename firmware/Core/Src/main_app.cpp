#include "main_app.h"

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

int main_app() {
  /* Initialization */
  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(EN_12V_GPIO_Port, EN_12V_Pin, GPIO_PIN_SET);
  
  while (1) {
    /* Super loop */
    // HAL_GPIO_TogglePin(EN_12V_GPIO_Port, EN_12V_Pin);
    // HAL_Delay(2000);
  }
}