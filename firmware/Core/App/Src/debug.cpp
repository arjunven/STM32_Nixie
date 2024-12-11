// debug.cpp

#include "debug.hh"

#include <cstdio>

extern "C" UART_HandleTypeDef huart2;

// Define static buffer
std::array<char, Debug::BUFFER_SIZE> Debug::buffer;

void Debug::put_char(char c) {
  HAL_UART_Transmit(&huart2, reinterpret_cast<uint8_t *>(&c), 1, HAL_MAX_DELAY);
}

void Debug::put_string(const char *str) {
  while (*str) {
    put_char(*str++);
  }
}

void Debug::printf(const char *format, ...) {
  static std::array<char, 256> buffer;  // Buffer for formatting
  va_list args;

  va_start(args, format);
  vsnprintf(buffer.data(), buffer.size(), format, args);
  va_end((args));

  put_string(buffer.data());
}