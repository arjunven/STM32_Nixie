cmake_minimum_required(VERSION 3.22)

# Create INTERFACE library
add_library(stm32cubemx INTERFACE)

# All source files are relative to this directory - define a variable to make paths cleaner
set(CUBEMX_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../..")

# Compiler definitions
target_compile_definitions(stm32cubemx 
    INTERFACE 
        USE_HAL_DRIVER 
        STM32F100xB
        $<$<CONFIG:Debug>:DEBUG>
)

# Include directories - using our root variable
target_include_directories(stm32cubemx 
    INTERFACE
        ${CUBEMX_ROOT_DIR}/Core/Inc
        ${CUBEMX_ROOT_DIR}/Drivers/STM32F1xx_HAL_Driver/Inc
        ${CUBEMX_ROOT_DIR}/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy
        ${CUBEMX_ROOT_DIR}/Drivers/CMSIS/Device/ST/STM32F1xx/Include
        ${CUBEMX_ROOT_DIR}/Drivers/CMSIS/Include
)

# Group source files by category for better organization
set(CORE_SOURCES
    ${CUBEMX_ROOT_DIR}/Core/Src/main.c
    ${CUBEMX_ROOT_DIR}/Core/Src/gpio.c
    ${CUBEMX_ROOT_DIR}/Core/Src/adc.c
    ${CUBEMX_ROOT_DIR}/Core/Src/rtc.c
    ${CUBEMX_ROOT_DIR}/Core/Src/spi.c
    ${CUBEMX_ROOT_DIR}/Core/Src/tim.c
    ${CUBEMX_ROOT_DIR}/Core/Src/usart.c
    ${CUBEMX_ROOT_DIR}/Core/Src/stm32f1xx_it.c
    ${CUBEMX_ROOT_DIR}/Core/Src/stm32f1xx_hal_msp.c
    ${CUBEMX_ROOT_DIR}/Core/Src/system_stm32f1xx.c
    ${CUBEMX_ROOT_DIR}/Core/Src/sysmem.c
    ${CUBEMX_ROOT_DIR}/Core/Src/syscalls.c
)

set(HAL_SOURCES
    ${CUBEMX_ROOT_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
    ${CUBEMX_ROOT_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc.c
    ${CUBEMX_ROOT_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc_ex.c
    ${CUBEMX_ROOT_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
    ${CUBEMX_ROOT_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c
    ${CUBEMX_ROOT_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c
    ${CUBEMX_ROOT_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c
    ${CUBEMX_ROOT_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c
    ${CUBEMX_ROOT_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
    ${CUBEMX_ROOT_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c
    ${CUBEMX_ROOT_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c
    ${CUBEMX_ROOT_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
    ${CUBEMX_ROOT_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c
    ${CUBEMX_ROOT_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rtc.c
    ${CUBEMX_ROOT_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rtc_ex.c
    ${CUBEMX_ROOT_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_spi.c
    ${CUBEMX_ROOT_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c
    ${CUBEMX_ROOT_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c
    ${CUBEMX_ROOT_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c
)

set(STARTUP_SOURCES
    ${CUBEMX_ROOT_DIR}/startup_stm32f100xb.s
)

# Add all sources to the library
target_sources(stm32cubemx 
    INTERFACE
        ${CORE_SOURCES}
        ${HAL_SOURCES}
        ${STARTUP_SOURCES}
)

# Validate C standard requirement
if(CMAKE_C_STANDARD LESS 11)
    message(FATAL_ERROR "Generated code requires C11 or higher")
endif()

# Add build warning when Debug mode is active
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Building STM32CubeMX code in Debug mode")
endif()