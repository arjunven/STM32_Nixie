cmake_minimum_required(VERSION 3.22)

# Define the build type early
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set project name
set(PROJECT_NAME stm32_nixie)

# Include toolchain file before project() command
include("cmake/gcc-arm-none-eabi.cmake")

# Project definition
project(${PROJECT_NAME} C CXX ASM)

# Enable compile command generation for tooling
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Global compiler settings - these complement the toolchain file settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Create target
add_executable(${PROJECT_NAME})

# Add sources
target_sources(${PROJECT_NAME}
    PRIVATE
        Core/App/Src/main_app.cpp
        Core/App/Src/hv5622_driver.cpp
        Core/App/Src/nixie_display.cpp
        Core/App/Src/system_control.cpp
        Core/App/Src/time_lord.cpp
        Core/App/Src/debug.cpp
)

# Configure includes
target_include_directories(${PROJECT_NAME}
    PRIVATE
        Core/Inc
        Core/App/Inc
)

# Add STM32CubeMX generated code
add_subdirectory(cmake/stm32cubemx)

# Compile options - using generator expressions for language-specific flags
# target_compile_options(${PROJECT_NAME}
#     PRIVATE
#         $<$<CONFIG:Debug>:-Og -g3>
#         $<$<CONFIG:Release>:-Os -g0>
#         $<$<COMPILE_LANGUAGE:CXX>:
#             -fno-rtti
#             -fno-exceptions
#             -fno-threadsafe-statics
#         >
# )

# Link libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        stm32cubemx
)

# Print final settings
get_target_property(TARGET_COMPILE_OPTIONS ${PROJECT_NAME} COMPILE_OPTIONS)
message(STATUS "Compile options: ${TARGET_COMPILE_OPTIONS}")