# Getting Started Guide

This guide will help you get up and running with the STM32 Rocket Engine Control template.

## Quick Start

### 1. Install Prerequisites

#### Linux (Ubuntu/Debian)

```bash
# Install ARM GCC Toolchain
sudo apt-get update
sudo apt-get install gcc-arm-none-eabi

# Install CMake
sudo apt-get install cmake

# Install build tools
sudo apt-get install build-essential

# Install OpenOCD (for flashing and debugging)
sudo apt-get install openocd

# Install ST-Link tools (optional, alternative to OpenOCD)
sudo apt-get install stlink-tools
```

#### macOS

```bash
# Install Homebrew (if not already installed)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install ARM GCC Toolchain
brew install --cask gcc-arm-embedded

# Install CMake
brew install cmake

# Install OpenOCD
brew install open-ocd

# Install ST-Link
brew install stlink
```

#### Windows

1. Download and install [ARM GCC Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm)
   - Add to PATH during installation

2. Download and install [CMake](https://cmake.org/download/)
   - Check "Add CMake to system PATH"

3. Download and install [STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html)

4. (Optional) Install [MinGW](http://www.mingw.org/) or use WSL for Unix-like environment

### 2. Verify Installation

```bash
# Check ARM GCC
arm-none-eabi-gcc --version

# Check CMake
cmake --version

# Check OpenOCD (optional)
openocd --version
```

Expected output:
```
arm-none-eabi-gcc (GNU Arm Embedded Toolchain ...) X.X.X
cmake version 3.XX.X
Open On-Chip Debugger X.X.X
```

### 3. Clone and Build

```bash
# Clone the repository
git clone <your-repository-url>
cd template

# Build the project
./build.sh release

# Or manually:
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/arm-none-eabi-gcc.cmake
make
```

### 4. Configure for Your Hardware

Edit `CMakeLists.txt` to match your STM32 model:

```cmake
# Change these lines for your specific MCU
set(MCU_FAMILY STM32F4xx)
set(MCU_MODEL STM32F407xx)
set(MCU_LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/STM32F407VGTx_FLASH.ld")
```

### 5. Flash to Board

```bash
cd build

# Using st-flash
st-flash write STM32_RocketEngine.bin 0x8000000

# Using OpenOCD
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg \
  -c "program STM32_RocketEngine.elf verify reset exit"
```

## Project Customization

### Changing Target MCU

If you're using a different STM32 model (e.g., STM32F103):

1. **Update CMakeLists.txt**:
   ```cmake
   set(MCU_FAMILY STM32F1xx)
   set(MCU_MODEL STM32F103xB)
   set(CPU "-mcpu=cortex-m3")
   set(FPU "")  # F1 series doesn't have FPU
   set(FLOAT_ABI "-mfloat-abi=soft")
   ```

2. **Get appropriate linker script**:
   - Use STM32CubeMX to generate linker script for your MCU
   - Or find it in STM32Cube firmware package
   - Update `MCU_LINKER_SCRIPT` path

3. **Get appropriate startup file**:
   - Use STM32CubeMX to generate startup file
   - Or find it in STM32Cube firmware package
   - Update startup file name in CMakeLists.txt

4. **Update device header**:
   - Replace `include/HAL/stm32f4xx.h` with correct header
   - Or download full CMSIS and HAL libraries

### Adding STM32 HAL Library

To use the official STM32 HAL library instead of the minimal implementation:

1. **Download STM32Cube package** for your MCU family

2. **Copy HAL files** to your project:
   ```bash
   mkdir -p Drivers/STM32F4xx_HAL_Driver
   mkdir -p Drivers/CMSIS
   
   # Copy HAL source and include files
   cp -r STM32Cube_FW_F4/Drivers/STM32F4xx_HAL_Driver/Src/* Drivers/STM32F4xx_HAL_Driver/
   cp -r STM32Cube_FW_F4/Drivers/STM32F4xx_HAL_Driver/Inc/* Drivers/STM32F4xx_HAL_Driver/
   
   # Copy CMSIS files
   cp -r STM32Cube_FW_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include/* Drivers/CMSIS/
   cp -r STM32Cube_FW_F4/Drivers/CMSIS/Include/* Drivers/CMSIS/
   ```

3. **Update CMakeLists.txt** to include HAL sources:
   ```cmake
   # Add HAL include directories
   include_directories(
       ${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc
       ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
       ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Include
       # ... existing includes
   )
   
   # Add HAL sources
   file(GLOB_RECURSE HAL_DRIVER_SOURCES "Drivers/STM32F4xx_HAL_Driver/Src/*.c")
   
   # Add to executable
   add_executable(${PROJECT_NAME}.elf
       # ... existing sources
       ${HAL_DRIVER_SOURCES}
   )
   ```

4. **Create HAL configuration file** `stm32f4xx_hal_conf.h`

5. **Update code** to use official HAL functions

## Development Workflow

### Typical Development Cycle

```bash
# 1. Edit source files
vim src/Controller/controller.c

# 2. Build
./build.sh debug

# 3. Flash to board
cd build
st-flash write STM32_RocketEngine.bin 0x8000000

# 4. Debug (optional)
arm-none-eabi-gdb STM32_RocketEngine.elf
```

### Using an IDE

#### Visual Studio Code

1. Install extensions:
   - C/C++
   - CMake Tools
   - Cortex-Debug

2. Open folder in VS Code

3. Configure CMake (Ctrl+Shift+P → CMake: Configure)

4. Build (Ctrl+Shift+P → CMake: Build)

5. Create `launch.json` for debugging:
   ```json
   {
       "version": "0.2.0",
       "configurations": [
           {
               "name": "Debug STM32",
               "type": "cortex-debug",
               "request": "launch",
               "servertype": "openocd",
               "cwd": "${workspaceRoot}",
               "executable": "${workspaceRoot}/build/STM32_RocketEngine.elf",
               "configFiles": [
                   "interface/stlink.cfg",
                   "target/stm32f4x.cfg"
               ]
           }
       ]
   }
   ```

#### CLion

1. Open project folder in CLion

2. CLion will automatically detect CMakeLists.txt

3. Configure toolchain in Settings:
   - File → Settings → Build, Execution, Deployment → Toolchains
   - Add new CMake toolchain
   - Set C Compiler to `arm-none-eabi-gcc`
   - Set C++ Compiler to `arm-none-eabi-g++`

4. Configure CMake options:
   - File → Settings → Build, Execution, Deployment → CMake
   - Add CMake option: `-DCMAKE_TOOLCHAIN_FILE=cmake/arm-none-eabi-gcc.cmake`

5. Build with Ctrl+F9

#### STM32CubeIDE

1. Import project: File → Open Projects from File System

2. Select the project folder

3. Configure build settings to use existing CMakeLists.txt

## Adding Custom Code

### Adding a New Sensor

1. **Create header file**: `include/Components/my_sensor.h`
   ```c
   #ifndef MY_SENSOR_H
   #define MY_SENSOR_H
   
   #include <stdint.h>
   
   void MySensor_Init(void);
   float MySensor_ReadValue(void);
   
   #endif
   ```

2. **Create source file**: `src/Components/my_sensor.c`
   ```c
   #include "my_sensor.h"
   #include "hal_init.h"
   
   void MySensor_Init(void) {
       // Initialize sensor
   }
   
   float MySensor_ReadValue(void) {
       uint16_t raw = HAL_ADC_Read(5);
       return (float)raw * 0.1f;
   }
   ```

3. **Use in DIL**: Update `src/DIL/engine_interface.c`
   ```c
   #include "my_sensor.h"
   
   void EngineInterface_Init(void) {
       // ... existing code
       MySensor_Init();
   }
   ```

4. **Rebuild**:
   ```bash
   ./build.sh
   ```

### Adding a State to Controller

1. **Update enum** in `include/Controller/controller.h`:
   ```c
   typedef enum {
       // ... existing states
       CONTROLLER_STATE_MY_NEW_STATE,
   } ControllerState_t;
   ```

2. **Add case** in `src/Controller/controller.c`:
   ```c
   void Controller_Run(void) {
       switch (current_state) {
           // ... existing cases
           
           case CONTROLLER_STATE_MY_NEW_STATE:
               // Your state logic here
               break;
       }
   }
   ```

## Debugging

### Using GDB

```bash
# Terminal 1: Start OpenOCD
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg

# Terminal 2: Start GDB
arm-none-eabi-gdb build/STM32_RocketEngine.elf

# In GDB:
(gdb) target remote localhost:3333
(gdb) monitor reset halt
(gdb) load
(gdb) break main
(gdb) continue
```

### Common GDB Commands

```gdb
# Set breakpoint
break main
break controller.c:123

# Step through code
step        # Step into functions
next        # Step over functions
continue    # Continue execution

# Inspect variables
print variable_name
print *pointer_name

# View stack trace
backtrace

# View registers
info registers
```

### Serial Debug Output

1. **Initialize UART** in your code

2. **Connect USB-to-Serial adapter** to UART pins

3. **Open terminal**:
   ```bash
   # Linux
   screen /dev/ttyUSB0 115200
   
   # macOS
   screen /dev/cu.usbserial 115200
   
   # Windows (use PuTTY)
   ```

## Next Steps

1. Read [ARCHITECTURE.md](ARCHITECTURE.md) to understand the layered design
2. Read [README.md](README.md) for comprehensive documentation
3. Customize HAL layer for your specific peripherals
4. Implement your sensors in Components layer
5. Create device interfaces in DIL layer
6. Implement your control logic in Controller layer

## Getting Help

Common issues and solutions:

**"arm-none-eabi-gcc not found"**
- Ensure ARM toolchain is installed and in PATH
- Verify with: `which arm-none-eabi-gcc`

**Build errors about missing headers**
- Check include paths in CMakeLists.txt
- Ensure all header files exist in include/ directories

**Flash errors**
- Check ST-Link connection
- Try different USB port
- Update ST-Link firmware

**Code doesn't run after flashing**
- Verify linker script matches your MCU memory
- Check startup code is correct for your MCU
- Verify clock configuration

For more detailed information, see the main [README.md](README.md) file.
