# template
Template repository. Repository name format: &lt;stm[model]|py|desktop>-&lt;project_name>-&lt;layer>  

Example:
- stmf411-engine-hal
- stm-engine-components

For the README.md file, it should be structured like the following:

---

# Project Name

> One-sentence summary describing what your project does or solves.

---

## Table of Contents
- [About](#about)
- [Project Structure](#project-structure)
- [Requirements](#requirements)
- [Installation / Build](#installation--build)
- [Usage](#usage)
- [Configuration](#configuration)
- [Troubleshooting](#troubleshooting)

---

## About

Explain what the project is, what problem it solves, and any relevant context.

Example:  
> This project implements the HAL layer of the engine project on the STMF411...

---

## Project Structure
project-root/  
│  
├── src/ # Source files  
├── include/ # Header files  
├── scripts/ # Utility scripts or build helpers  
├── config/ # Configuration or calibration files  
├── docs/ # Documentation and manuals  
├── tests/ # Unit or integration tests  
└── README.md  

---

## Requirements

List any hardware, software, or library dependencies needed to build or run the project.

Example:

- **Hardware:** STM32F4 Series, Raspberry Pi 4  
- **Compiler:** GCC 13+ or ARM-GCC toolchain  
- **Libraries:**  
  - HAL Drivers (for STM32)  
  - WiringPi (for Raspberry Pi)  
  - CMake ≥ 3.20  

---

## Installation / Build

List of steps required to install and build the project.

Example:

- Clone the project
- Download Visual Studio 2022 from this [Link](#www.duckduckgo.com)
- Open the sln file with Visual Studio
- Run the build

## Usage

List of steps required to run and/or debug the project.

Example:
- Open the project with Visual Studio 2022
- Press the `start` button

## Configuration

List of configuration files if any

Example:
- vcpkg.json
- .clang-tidy
- .clang-format

## Troubleshooting

QA kind of section with the most common problems and how to fix them

> The application build fails after the installation

Make sure that the vcpkg modules have been downloaded. Check the `use manifest` option in Visual Studio to see if the modules are downloaded automatically or not
