// debug.h

#ifndef DEBUG_H
#define DEBUG_H

#include <array>
#include <cstdarg>
#include <cstdint>

#include "usart.h"

class Debug {
 public:
  static void printf(const char* format, ...);

 private:
  static void put_char(char c);
  static void put_string(const char* str);

  // Buffer for formatting strings
  static constexpr size_t BUFFER_SIZE = 256;
  static std::array<char, BUFFER_SIZE> buffer;
};

#endif