# STM32 Rocket Engine Control Template

Template repository for STM32 embedded development projects focused on rocket engine control systems. This project uses CMake and is structured with a layered architecture for maintainability and modularity.

Repository name format: `<stm[model]|py|desktop>-<project_name>-<layer>`

## Project Structure

The project follows a layered architecture with clear separation of concerns:

```
├── src/
│   ├── HAL/              # Hardware Abstraction Layer
│   ├── Components/       # Hardware component drivers
│   ├── DIL/              # Device Interface Layer
│   └── Controller/       # Application logic and control algorithms
├── include/
│   ├── HAL/
│   ├── Components/
│   ├── DIL/
│   └── Controller/
├── cmake/                # CMake toolchain files
├── CMakeLists.txt        # Main build configuration
├── startup_stm32f407xx.s # Startup assembly file
└── STM32F407VGTx_FLASH.ld # Linker script
```

### Architecture Layers

#### 1. HAL (Hardware Abstraction Layer)
- Lowest level interface to hardware peripherals
- Direct access to STM32 registers and peripherals
- Provides basic initialization and control functions for GPIO, timers, ADC, UART, etc.

**Files:**
- `include/HAL/hal_init.h`
- `src/HAL/hal_init.c`
- `include/HAL/stm32f4xx.h`

#### 2. Components Layer
- Hardware component drivers for sensors, actuators, and communication modules
- Abstracts specific hardware components (sensors, valves, etc.)
- Uses HAL layer for low-level operations

**Files:**
- `include/Components/sensors.h`
- `src/Components/sensors.c`

#### 3. DIL (Device Interface Layer)
- High-level, abstract interface to devices
- Hides component-specific implementation details
- Provides logical device operations (e.g., engine control, valve management)

**Files:**
- `include/DIL/engine_interface.h`
- `src/DIL/engine_interface.c`

#### 4. Controller Layer
- Highest level application logic
- Implements control algorithms and state machines
- Orchestrates all lower layers for complete application functionality

**Files:**
- `include/Controller/controller.h`
- `src/Controller/controller.c`

## Prerequisites

### Required Software

1. **ARM GCC Toolchain**
   - Download from: https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm
   - Add to system PATH

2. **CMake** (version 3.20 or higher)
   - Download from: https://cmake.org/download/
   - Or install via package manager:
     ```bash
     # Ubuntu/Debian
     sudo apt-get install cmake
     
     # macOS
     brew install cmake
     ```

3. **Build Tools**
   - Linux: `sudo apt-get install build-essential`
   - macOS: Install Xcode Command Line Tools
   - Windows: Install MinGW or use WSL

4. **ST-Link Utility** (for flashing)
   - Download from STMicroelectronics website
   - Or use OpenOCD: `sudo apt-get install openocd`

### Optional Tools

- **STM32CubeMX**: For peripheral configuration and HAL code generation
- **Serial Terminal**: PuTTY, minicom, or screen for UART communication
- **IDE**: Visual Studio Code, CLion, or STM32CubeIDE

## Setup Instructions

### 1. Clone the Repository

```bash
git clone <repository-url>
cd template
```

### 2. Configure for Your Target MCU

Edit `CMakeLists.txt` to match your specific STM32 target:

```cmake
# Update these lines for your MCU
set(MCU_FAMILY STM32F4xx)
set(MCU_MODEL STM32F407xx)
set(MCU_LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/STM32F407VGTx_FLASH.ld")
```

If using a different STM32 model:
1. Update the linker script (`.ld` file) with correct memory sizes
2. Update the startup file (`.s` file) with correct vector table
3. Update CPU flags in CMakeLists.txt if needed

### 3. Build the Project

#### Using Command Line

```bash
# Create build directory
mkdir build
cd build

# Configure CMake with ARM toolchain
cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/arm-none-eabi-gcc.cmake

# Build the project
cmake --build .
```

This will generate:
- `STM32_RocketEngine.elf` - ELF executable
- `STM32_RocketEngine.hex` - Intel HEX format for flashing
- `STM32_RocketEngine.bin` - Binary format for flashing
- `STM32_RocketEngine.map` - Memory map file

#### Using Make

```bash
cd build
make
```

### 4. Flash to MCU

#### Using ST-Link

```bash
# Using st-flash
st-flash write STM32_RocketEngine.bin 0x8000000

# Or using OpenOCD
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program STM32_RocketEngine.elf verify reset exit"
```

#### Using STM32CubeProgrammer

1. Open STM32CubeProgrammer
2. Connect to the board via ST-Link
3. Load the `.hex` or `.bin` file
4. Click "Download"

### 5. Debug

#### Using GDB

```bash
# Start OpenOCD (in one terminal)
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg

# Start GDB (in another terminal)
arm-none-eabi-gdb build/STM32_RocketEngine.elf
(gdb) target remote localhost:3333
(gdb) monitor reset halt
(gdb) load
(gdb) continue
```

## Development Workflow

### Adding New Features

1. **New Sensor/Component**
   - Add header in `include/Components/`
   - Implement in `src/Components/`
   - Update CMakeLists.txt if needed

2. **New Device Interface**
   - Add header in `include/DIL/`
   - Implement in `src/DIL/`
   - Use Components layer functions

3. **New Control Logic**
   - Add to `include/Controller/controller.h`
   - Implement in `src/Controller/controller.c`
   - Use DIL functions

### Customization

#### Changing MCU Target

1. Update `CMakeLists.txt`:
   - Change `MCU_FAMILY` and `MCU_MODEL`
   - Update CPU flags (`CPU`, `FPU`, `FLOAT_ABI`)
   
2. Replace linker script (`.ld`) with your MCU's memory layout

3. Replace startup file (`.s`) with your MCU's vector table

4. Update `stm32f4xx.h` or include proper CMSIS headers

#### Adding STM32 HAL Library

If you want to use the official STM32 HAL library:

1. Download STM32CubeF4 package
2. Copy HAL sources to your project
3. Update CMakeLists.txt to include HAL sources
4. Replace minimal `stm32f4xx.h` with official CMSIS headers

## Project Configuration

### Compiler Flags

Defined in `CMakeLists.txt`:
- `-Wall -Wextra`: Enable warnings
- `-fdata-sections -ffunction-sections`: Enable garbage collection of unused sections
- `-O0 -g3`: Debug build (no optimization, full debug info)
- `-O2`: Release build (optimize for speed)

### Linker Flags

- `-specs=nano.specs`: Use newlib-nano for smaller code size
- `--gc-sections`: Remove unused sections
- `-Wl,-Map=`: Generate map file

## Troubleshooting

### Build Errors

**"arm-none-eabi-gcc not found"**
- Install ARM GCC toolchain and add to PATH
- Verify with: `arm-none-eabi-gcc --version`

**"undefined reference to"**
- Check that all source files are included in CMakeLists.txt
- Verify function declarations match implementations

### Flash Errors

**"Could not find device"**
- Check ST-Link connection
- Install ST-Link drivers
- Try different USB port

**"Flash loader run error"**
- Verify correct linker script for your MCU
- Check memory addresses in linker script
- Ensure binary size doesn't exceed flash memory

### Runtime Issues

**Program doesn't start**
- Check vector table location
- Verify startup code matches MCU
- Check clock configuration

**Hard fault**
- Enable fault handlers in startup code
- Use debugger to find fault location
- Check stack size in linker script

## Additional Resources

- [STM32F4 Reference Manual](https://www.st.com/resource/en/reference_manual/dm00031020.pdf)
- [ARM Cortex-M4 Technical Reference Manual](https://developer.arm.com/documentation/100166/0001/)
- [CMake Documentation](https://cmake.org/documentation/)
- [GNU ARM Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm)

## Safety Notice

This template is designed for rocket engine control systems. Always follow proper safety protocols:
- Implement multiple safety interlocks
- Test thoroughly in simulation before hardware testing
- Have emergency shutdown procedures
- Follow all applicable regulations and safety standards
- Never operate engine systems without proper safety equipment and trained personnel

## License

This is a template project. Add your license information here.

## Contributing

Contributions are welcome. Please follow the existing code structure and layered architecture when submitting changes.
