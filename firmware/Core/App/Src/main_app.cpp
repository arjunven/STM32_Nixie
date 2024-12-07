#include "main_app.hh"

#include <array>

#include "adc.h"
#include "gpio.h"
#include "hv5622_driver.hh"
#include "main.h"
#include "nixie_display.hh"
#include "rtc.h"
#include "spi.h"
#include "system_control.hh"
#include "tim.h"
#include "usart.h"

// Using the separate main_app because CubeMX code generation will keep making a
// new main.c and clobbers the main.cpp. Instead this main_app gets called in
// main.c so CubeMX can happily keep generating code.

uint16_t LED_DELAY = 1000;  // ms
uint8_t TUBE_S2 = 5;
uint8_t TUBE_S1 = 4;
uint8_t TUBE_M2 = 3;
uint8_t TUBE_M1 = 2;
uint8_t TUBE_H2 = 1;
uint8_t TUBE_H1 = 0;

// These tell the C++ compiler that these symbols come from C code
extern "C" {
extern SPI_HandleTypeDef hspi1;    // Defined in spi.c
extern ADC_HandleTypeDef hadc1;    // Defined in adc.c
extern RTC_HandleTypeDef hrtc;     // Defined in rtc.c
extern TIM_HandleTypeDef htim2;    // Defined in tim.c
extern UART_HandleTypeDef huart1;  // Defined in usart.c
extern UART_HandleTypeDef huart2;  // Defined in usart.c
}

int main_app() {
  /* Initialization */
  system_control::gpio_init();

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

  volatile bool power_good = system_control::power_up();

  if (!power_good) {
    system_control::power_down();
    system_control::enable_fault_led();
  }

  std::array<uint8_t, Nixie_display::NUM_TUBES> numbers = {0, 0, 0, 0, 0, 0};
  display.set_display(numbers);
  display.enable();

  while (1) {
    /* Super loop */
    for (uint8_t time = 0; time <= Nixie_display::MAX_DIGIT; time++) {
      numbers[TUBE_H1] = time;
      numbers[TUBE_H2] = time;
      numbers[TUBE_M1] = time;
      numbers[TUBE_M2] = time;
      numbers[TUBE_S1] = time;
      numbers[TUBE_S2] = time;
      display.set_display(numbers);
      HAL_Delay(1000);
    }
  }
}
