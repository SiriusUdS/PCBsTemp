/**
  ******************************************************************************
  * @file           : engine_interface.h
  * @brief          : Engine device interface layer header
  ******************************************************************************
  * @attention
  *
  * Device Interface Layer (DIL) - Abstract interface to devices
  * This layer provides a high-level, abstract interface to devices,
  * hiding component-specific implementation details
  *
  ******************************************************************************
  */

#ifndef ENGINE_INTERFACE_H
#define ENGINE_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/**
  * @brief  Engine status enumeration
  */
typedef enum {
    ENGINE_STATUS_IDLE = 0,
    ENGINE_STATUS_READY,
    ENGINE_STATUS_RUNNING,
    ENGINE_STATUS_FAULT,
    ENGINE_STATUS_SHUTDOWN
} EngineStatus_t;

/**
  * @brief  Engine parameters structure
  */
typedef struct {
    float chamber_temperature;
    float chamber_pressure;
    float fuel_flow_rate;
    float oxidizer_flow_rate;
    float thrust;
    EngineStatus_t status;
} EngineParams_t;

/* Engine Interface Initialization */
void EngineInterface_Init(void);

/* Engine Control Functions */
void EngineInterface_Start(void);
void EngineInterface_Stop(void);
void EngineInterface_SetThrottle(float throttle_percent);

/* Engine Monitoring Functions */
void EngineInterface_GetParameters(EngineParams_t *params);
EngineStatus_t EngineInterface_GetStatus(void);
bool EngineInterface_CheckSafety(void);

/* Valve Control Functions */
void EngineInterface_OpenValve(uint8_t valve_id);
void EngineInterface_CloseValve(uint8_t valve_id);

/* Ignition Control */
void EngineInterface_TriggerIgnition(void);

#ifdef __cplusplus
}
#endif

#endif /* ENGINE_INTERFACE_H */
