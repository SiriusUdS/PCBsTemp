cmake_minimum_required(VERSION 3.20)

# Project configuration
project(STM32_RocketEngine C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# STM32 MCU configuration - Update these for your specific target
set(MCU_FAMILY STM32F4xx)
set(MCU_MODEL STM32F407xx)
set(MCU_LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/STM32F407VGTx_FLASH.ld")

# CPU and FPU options for STM32F4 series
set(CPU "-mcpu=cortex-m4")
set(FPU "-mfpu=fpv4-sp-d16")
set(FLOAT_ABI "-mfloat-abi=hard")

# Compiler flags
set(COMMON_FLAGS "${CPU} -mthumb ${FPU} ${FLOAT_ABI}")
set(CMAKE_C_FLAGS "${COMMON_FLAGS} -Wall -Wextra -fdata-sections -ffunction-sections")
set(CMAKE_C_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_C_FLAGS_RELEASE "-O2")

# Linker flags
set(CMAKE_EXE_LINKER_FLAGS "${COMMON_FLAGS} -specs=nano.specs -T${MCU_LINKER_SCRIPT} -Wl,--gc-sections -Wl,-Map=${PROJECT_NAME}.map")

# Definitions
add_compile_definitions(
    ${MCU_MODEL}
    USE_HAL_DRIVER
)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include/HAL
    ${CMAKE_SOURCE_DIR}/include/Components
    ${CMAKE_SOURCE_DIR}/include/DIL
    ${CMAKE_SOURCE_DIR}/include/Controller
)

# Source files - Add your source files here
file(GLOB_RECURSE HAL_SOURCES "src/HAL/*.c")
file(GLOB_RECURSE COMPONENT_SOURCES "src/Components/*.c")
file(GLOB_RECURSE DIL_SOURCES "src/DIL/*.c")
file(GLOB_RECURSE CONTROLLER_SOURCES "src/Controller/*.c")

# Main executable
add_executable(${PROJECT_NAME}.elf
    src/main.c
    startup_stm32f407xx.s
    ${HAL_SOURCES}
    ${COMPONENT_SOURCES}
    ${DIL_SOURCES}
    ${CONTROLLER_SOURCES}
)

# Generate additional output formats
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
    COMMAND ${CMAKE_SIZE} ${PROJECT_NAME}.elf
    COMMENT "Building HEX and BIN files"
)

# Print build configuration
message(STATUS "MCU Family: ${MCU_FAMILY}")
message(STATUS "MCU Model: ${MCU_MODEL}")
message(STATUS "Linker Script: ${MCU_LINKER_SCRIPT}")
