#!/bin/bash

# Build script for STM32 Rocket Engine Control Project
# Usage: ./build.sh [clean|debug|release]

set -e

PROJECT_ROOT="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="$PROJECT_ROOT/build"
TOOLCHAIN_FILE="$PROJECT_ROOT/cmake/arm-none-eabi-gcc.cmake"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

print_info() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Check if ARM toolchain is installed
check_toolchain() {
    if ! command -v arm-none-eabi-gcc &> /dev/null; then
        print_error "ARM GCC toolchain not found!"
        print_info "Please install arm-none-eabi-gcc and add it to your PATH"
        print_info "Download from: https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm"
        exit 1
    fi
    
    print_info "ARM GCC version: $(arm-none-eabi-gcc --version | head -n1)"
}

# Clean build directory
clean_build() {
    print_info "Cleaning build directory..."
    if [ -d "$BUILD_DIR" ]; then
        rm -rf "$BUILD_DIR"
        print_info "Build directory cleaned"
    else
        print_warning "Build directory does not exist"
    fi
}

# Configure and build project
build_project() {
    local build_type=$1
    
    print_info "Building project (Build type: $build_type)..."
    
    # Create build directory if it doesn't exist
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"
    
    # Configure with CMake
    print_info "Configuring with CMake..."
    cmake .. \
        -DCMAKE_TOOLCHAIN_FILE="$TOOLCHAIN_FILE" \
        -DCMAKE_BUILD_TYPE="$build_type"
    
    # Build
    print_info "Compiling..."
    cmake --build . -- -j$(nproc)
    
    # Check if build succeeded
    if [ -f "STM32_RocketEngine.elf" ]; then
        print_info "Build successful!"
        print_info "Generated files:"
        ls -lh *.elf *.hex *.bin *.map 2>/dev/null || true
        
        # Display size information
        print_info "Size information:"
        arm-none-eabi-size STM32_RocketEngine.elf
    else
        print_error "Build failed!"
        exit 1
    fi
}

# Main script
main() {
    cd "$PROJECT_ROOT"
    
    print_info "STM32 Rocket Engine Control - Build Script"
    echo "=========================================="
    
    check_toolchain
    
    case "${1:-release}" in
        clean)
            clean_build
            ;;
        debug)
            build_project "Debug"
            ;;
        release)
            build_project "Release"
            ;;
        *)
            print_error "Unknown option: $1"
            echo "Usage: $0 [clean|debug|release]"
            exit 1
            ;;
    esac
    
    print_info "Done!"
}

main "$@"
