# Architecture Documentation

## Layered Architecture Overview

This project uses a four-layer architecture designed for embedded systems development. Each layer has a specific responsibility and communicates only with adjacent layers.

```
┌─────────────────────────────────────────────────┐
│          Controller Layer (Highest)             │
│  - Application logic & state machines           │
│  - Control algorithms                           │
│  - Decision making                              │
└─────────────────────────────────────────────────┘
                      ↕
┌─────────────────────────────────────────────────┐
│     Device Interface Layer (DIL)                │
│  - Abstract device operations                   │
│  - Device-level logic                           │
│  - Hides component implementation details       │
└─────────────────────────────────────────────────┘
                      ↕
┌─────────────────────────────────────────────────┐
│          Components Layer                       │
│  - Hardware component drivers                   │
│  - Sensor/actuator interfaces                   │
│  - Component-specific logic                     │
└─────────────────────────────────────────────────┘
                      ↕
┌─────────────────────────────────────────────────┐
│    Hardware Abstraction Layer (HAL) (Lowest)    │
│  - Direct hardware access                       │
│  - Register-level operations                    │
│  - Peripheral initialization                    │
└─────────────────────────────────────────────────┘
```

## Layer Responsibilities

### 1. Hardware Abstraction Layer (HAL)

**Purpose**: Provide low-level access to hardware peripherals

**Responsibilities**:
- Initialize MCU peripherals (GPIO, UART, ADC, Timers)
- Read/write hardware registers
- Configure peripheral settings
- Handle basic hardware operations

**Example Functions**:
```c
void HAL_GPIO_Init(void);
void HAL_GPIO_WritePin(uint32_t port, uint16_t pin, uint8_t state);
uint8_t HAL_GPIO_ReadPin(uint32_t port, uint16_t pin);
uint16_t HAL_ADC_Read(uint8_t channel);
```

**Files**:
- `include/HAL/hal_init.h`
- `src/HAL/hal_init.c`
- `include/HAL/stm32f4xx.h`

**Dependencies**: None (lowest layer)

---

### 2. Components Layer

**Purpose**: Implement drivers for specific hardware components

**Responsibilities**:
- Interface with specific sensors and actuators
- Convert raw hardware values to meaningful units
- Implement component-specific protocols
- Provide component-specific functionality

**Example Functions**:
```c
void Sensors_Init(void);
float Sensors_ReadTemperature(uint8_t sensor_id);
float Sensors_ReadPressure(uint8_t sensor_id);
float Sensors_ReadFlowRate(uint8_t sensor_id);
```

**Files**:
- `include/Components/sensors.h`
- `src/Components/sensors.c`

**Dependencies**: HAL Layer

**Examples of Components**:
- Temperature sensors
- Pressure sensors
- Flow rate sensors
- Valve drivers
- Motor controllers
- Communication modules

---

### 3. Device Interface Layer (DIL)

**Purpose**: Provide abstract, high-level interface to logical devices

**Responsibilities**:
- Abstract away component implementation details
- Coordinate multiple components for device operations
- Implement device-level safety checks
- Provide logical device operations

**Example Functions**:
```c
void EngineInterface_Init(void);
void EngineInterface_Start(void);
void EngineInterface_Stop(void);
void EngineInterface_SetThrottle(float throttle_percent);
void EngineInterface_OpenValve(uint8_t valve_id);
bool EngineInterface_CheckSafety(void);
```

**Files**:
- `include/DIL/engine_interface.h`
- `src/DIL/engine_interface.c`

**Dependencies**: Components Layer, HAL Layer

**Key Concept**: DIL treats the combination of components as a single logical device (e.g., "Engine" instead of separate sensors and valves)

---

### 4. Controller Layer

**Purpose**: Implement application logic and control algorithms

**Responsibilities**:
- Main application state machine
- High-level control algorithms
- Command processing
- System coordination
- Safety monitoring
- User interface logic

**Example Functions**:
```c
void Controller_Init(void);
void Controller_Run(void);
bool Controller_Arm(void);
bool Controller_StartEngine(void);
bool Controller_StopEngine(void);
void Controller_EmergencyShutdown(void);
```

**Files**:
- `include/Controller/controller.h`
- `src/Controller/controller.c`

**Dependencies**: DIL Layer

**Key Concept**: Controller orchestrates all system operations without knowing hardware implementation details

---

## Communication Rules

### Allowed Interactions

1. **Controller → DIL**: ✅ Controller calls DIL functions
2. **DIL → Components**: ✅ DIL uses component drivers
3. **Components → HAL**: ✅ Components use HAL functions
4. **DIL → HAL**: ✅ DIL can directly use HAL if needed

### Prohibited Interactions

1. **Controller → Components**: ❌ Controller should not bypass DIL
2. **Controller → HAL**: ❌ Controller should not access hardware directly
3. **DIL → Controller**: ❌ No upward dependencies
4. **Components → DIL**: ❌ No upward dependencies

## Example Data Flow

### Reading Engine Temperature

```
1. Controller_Run()
   └─> 2. EngineInterface_GetParameters()
          └─> 3. Sensors_GetData()
                 └─> 4. Sensors_ReadTemperature()
                        └─> 5. HAL_ADC_Read()
                               └─> 6. [Hardware Register Access]
```

### Starting the Engine

```
1. Controller_StartEngine()
   └─> 2. EngineInterface_Start()
          ├─> 3a. EngineInterface_CheckSafety()
          │      └─> Sensors_GetData()
          │
          ├─> 3b. EngineInterface_OpenValve()
          │      └─> HAL_GPIO_WritePin()
          │
          └─> 3c. EngineInterface_TriggerIgnition()
                 └─> HAL_GPIO_WritePin()
```

## Benefits of This Architecture

### 1. Separation of Concerns
- Each layer has a single, well-defined responsibility
- Changes to one layer have minimal impact on others

### 2. Maintainability
- Easy to locate and fix bugs
- Clear boundaries between different system aspects
- Simplified testing and debugging

### 3. Reusability
- HAL can be reused across different projects
- Components can be swapped without affecting upper layers
- DIL provides a stable interface for multiple applications

### 4. Testability
- Each layer can be tested independently
- Easy to create mock implementations for testing
- Unit tests can focus on specific layer functionality

### 5. Scalability
- New components can be added without changing DIL or Controller
- New devices can be added at DIL level
- Application logic can evolve independently

## Adding New Functionality

### Adding a New Sensor (Component)

1. Create `include/Components/new_sensor.h`
2. Implement `src/Components/new_sensor.c`
3. Use HAL functions for hardware access
4. Update DIL to use the new sensor if needed

### Adding a New Device (DIL)

1. Create `include/DIL/new_device.h`
2. Implement `src/DIL/new_device.c`
3. Use Components and HAL layers
4. Update Controller to use the new device

### Adding Control Logic

1. Update `include/Controller/controller.h`
2. Implement in `src/Controller/controller.c`
3. Use DIL functions only
4. No direct hardware access

## Best Practices

1. **Keep dependencies unidirectional** (only downward in the stack)
2. **Use appropriate abstraction levels** (don't expose hardware details in upper layers)
3. **Document interfaces clearly** (each function should have a clear purpose)
4. **Handle errors at appropriate layers** (hardware errors in HAL, device errors in DIL, etc.)
5. **Use type definitions** (enums, structs) to make interfaces clear
6. **Implement safety checks at multiple layers** (defense in depth)

## For Rocket Engine Control

This layered architecture is particularly important for safety-critical systems like rocket engine control:

- **HAL**: Ensures reliable hardware communication
- **Components**: Provides accurate sensor readings and actuator control
- **DIL**: Implements device-level safety interlocks
- **Controller**: Manages overall system state and safety logic

Multiple layers of safety checks ensure that dangerous conditions are detected and handled appropriately at every level of the system.
