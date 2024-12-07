set(CMAKE_SYSTEM_NAME               Generic)
set(CMAKE_SYSTEM_PROCESSOR          arm)

# Enforce compiler ID checks
set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)
set(CMAKE_C_COMPILER_ID GNU)
set(CMAKE_CXX_COMPILER_ID GNU)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set toolchain paths
set(TOOLCHAIN_PREFIX                /opt/ST/STM32CubeCLT_1.16.0/GNU-tools-for-STM32/bin/arm-none-eabi-)
set(CMAKE_C_COMPILER                ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_ASM_COMPILER              ${CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER              ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_LINKER                    ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_OBJCOPY                   ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_SIZE                      ${TOOLCHAIN_PREFIX}size)

# Set executable suffix
set(CMAKE_EXECUTABLE_SUFFIX_ASM     ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C       ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX     ".elf")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# MCU specific flags
set(TARGET_FLAGS "-mcpu=cortex-m3")

# Common flags for all languages
set(COMMON_FLAGS 
    ${TARGET_FLAGS}
    -Wall
    -Wextra 
    -Wpedantic
    -fdata-sections
    -ffunction-sections
)

# Debug/Release specific flags
if(CMAKE_BUILD_TYPE MATCHES Debug)
    list(APPEND COMMON_FLAGS "-Os" "-g3")
else()
    list(APPEND COMMON_FLAGS "-Os" "-g0")
endif()

# Convert list to space-separated string
string(REPLACE ";" " " COMMON_FLAGS_STR "${COMMON_FLAGS}")

# Set language specific flags
set(CMAKE_C_FLAGS "${COMMON_FLAGS_STR}")
set(CMAKE_ASM_FLAGS "${COMMON_FLAGS_STR} -x assembler-with-cpp")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS_STR} -fno-rtti -fno-exceptions -fno-threadsafe-statics")

# Use nano specs for linking
set(CMAKE_EXE_LINKER_FLAGS_INIT "")

# Core linker flags
list(APPEND CMAKE_EXE_LINKER_FLAGS_INIT
    "${TARGET_FLAGS}"
    "-T\"${CMAKE_SOURCE_DIR}/STM32F100C4Tx_FLASH.ld\""
    "-Wl,-Map=${CMAKE_PROJECT_NAME}.map,--gc-sections"
    "-Wl,--print-memory-usage"
)

# Convert list to space-separated string
string(REPLACE ";" " " CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS_INIT}")

# Set nano spec through proper CMake variable
set(CMAKE_C_STANDARD_LIBRARIES "--specs=nano.specs")
set(CMAKE_CXX_STANDARD_LIBRARIES "--specs=nano.specs -Wl,--start-group -lstdc++ -lsupc++ -Wl,--end-group")

# After setting flags
message(STATUS "TOOLCHAIN: C++ FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "TOOLCHAIN: C FLAGS: ${CMAKE_C_FLAGS}")
message(STATUS "TOOLCHAIN: COMMON FLAGS: ${COMMON_FLAGS_STR}")