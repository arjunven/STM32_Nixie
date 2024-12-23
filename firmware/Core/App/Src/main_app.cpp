// main_app.cpp

#include "main_app.hh"

#include <array>

#include "debug.hh"
#include "hv5622_driver.hh"
#include "main.h"
#include "menu.hh"
#include "nixie_display.hh"
#include "system_control.hh"
#include "time_lord.hh"
#include "user_input.hh"

// Using the separate main_app because CubeMX code generation will keep making a
// new main.c and clobbers the main.cpp. Instead this main_app gets called in
// main.c so CubeMX can happily keep generating code.

uint16_t LED_DELAY = 1000;  // ms

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

  // Debug::printf("Hello %s! Count %d\n", "World", 44);

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
  initial_time.Minutes = 0x37;
  initial_time.Seconds = 0x00;

  // Initialize time keeper, user input, and menu
  static Time_lord chronos(display, &hrtc, initial_time);
  static User_input input(&htim2, ENC_PB_GPIO_Port, ENC_PB_Pin);
  static Menu menu(chronos, display);

  volatile int8_t movement;

  // std::array<bool, Nixie_display::NUM_TUBES> blinky = {
  //     false, false, true, true, false, false};
  // display.set_blinking_positions(blinky);

  /* Super loop */
  while (true) {
    input.update();
    movement = input.get_encoder_movement();  // debug
    chronos.update();
    menu.update(input);
    display.update();
    HAL_Delay(1);
  }
}
