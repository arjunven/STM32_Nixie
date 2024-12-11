// main_app.cpp

#include "main_app.hh"

#include <array>

#include "debug.hh"
#include "hv5622_driver.hh"
#include "main.h"
#include "nixie_display.hh"
#include "system_control.hh"
#include "time_lord.hh"

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

  Debug::printf("Hello %s! Count %d\n", "World", 44);

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

  // hard coded initial time for now
  RTC_TimeTypeDef initial_time;
  initial_time.Hours = 0x22;
  initial_time.Minutes = 0x17;
  initial_time.Seconds = 0x00;

  static Time_lord chronos(display, &hrtc, initial_time);

  // std::array<uint8_t, Nixie_display::NUM_TUBES> numbers = {0, 0, 0, 0, 0, 0};
  // display.set_display(numbers);
  // display.enable();

  volatile bool status;

  /* Super loop */
  while (true) {
    status = chronos.update_display();
  }
}
