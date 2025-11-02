# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2025-10-13

### Added
- Initial project structure with layered architecture
- HAL (Hardware Abstraction Layer) implementation
  - GPIO, UART, ADC, Timer initialization functions
  - Minimal STM32F4xx device header
- Components layer implementation
  - Sensor drivers for temperature, pressure, and flow rate
  - Example component implementations
- DIL (Device Interface Layer) implementation
  - Engine interface for rocket control
  - Valve control functions
  - Safety check functions
- Controller layer implementation
  - Main state machine for engine control
  - Control algorithms and command processing
  - Safety monitoring and emergency shutdown
- CMake build system
  - ARM GCC toolchain configuration
  - STM32F407 target configuration
  - Automatic generation of HEX and BIN files
- Build automation
  - build.sh script for easy compilation
  - Support for Debug and Release builds
- STM32F407 specific files
  - Linker script (STM32F407VGTx_FLASH.ld)
  - Startup assembly code (startup_stm32f407xx.s)
- Comprehensive documentation
  - README.md with complete setup instructions
  - ARCHITECTURE.md with detailed layer documentation
  - GETTING_STARTED.md with step-by-step guide
- VS Code integration examples
  - settings.json.example for project configuration
  - launch.json.example for debugging
  - tasks.json.example for build automation
- Git configuration
  - .gitignore for build artifacts and IDE files

### Project Structure
```
├── src/                      # Source files organized by layer
│   ├── HAL/                  # Hardware abstraction
│   ├── Components/           # Hardware component drivers
│   ├── DIL/                  # Device interface layer
│   ├── Controller/           # Application logic
│   └── main.c                # Entry point
├── include/                  # Header files organized by layer
│   ├── HAL/
│   ├── Components/
│   ├── DIL/
│   └── Controller/
├── cmake/                    # CMake configuration files
├── .vscode/                  # VS Code configuration examples
├── Documentation files       # README, ARCHITECTURE, GETTING_STARTED
└── Build configuration       # CMakeLists.txt, linker script, startup code
```

### Features
- **Modular Design**: Four-layer architecture for maintainability
- **Safety-First**: Multiple layers of safety checks for critical systems
- **Cross-Platform Build**: CMake-based build system
- **Embedded-Ready**: Configured for STM32F407, easily adaptable
- **Well-Documented**: Comprehensive guides for setup and development
- **IDE Support**: Example configurations for Visual Studio Code

### Target Hardware
- Primary target: STM32F407VGTx
- CPU: ARM Cortex-M4 with FPU
- Memory: 1024KB Flash, 128KB RAM, 64KB CCM RAM

### Requirements
- ARM GCC toolchain (arm-none-eabi-gcc)
- CMake 3.20 or higher
- ST-Link programmer or OpenOCD
- (Optional) STM32CubeMX for additional HAL code generation

### Notes
- This is a template project intended as a starting point
- Customization required for specific hardware configurations
- HAL implementation is minimal; consider using official STM32 HAL for production
- Designed specifically for rocket engine control applications

## [Unreleased]

### Future Enhancements
- [ ] Add example unit tests
- [ ] Include Doxygen documentation generation
- [ ] Add more example components (motor controllers, communication modules)
- [ ] Include example safety interlocks
- [ ] Add CAN bus communication example
- [ ] Include real-time operating system (RTOS) integration example
- [ ] Add configuration for additional STM32 families (F1, F3, H7, etc.)
- [ ] Include calibration and configuration management
- [ ] Add data logging capabilities
- [ ] Include example telemetry format and protocol

---

## Version History

- **1.0.0** (2025-10-13): Initial release with complete layered architecture

## Contributing

When contributing to this project, please:
1. Update this CHANGELOG.md with your changes
2. Follow the existing code structure and layered architecture
3. Add appropriate documentation for new features
4. Test thoroughly before submitting changes
