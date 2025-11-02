/**
  ******************************************************************************
  * @file           : controller.h
  * @brief          : Main controller header
  ******************************************************************************
  * @attention
  *
  * Controller Layer - Application logic and control algorithms
  * This is the highest level layer that implements the control logic,
  * state machines, and application-level functionality
  *
  ******************************************************************************
  */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/**
  * @brief  Controller state enumeration
  */
typedef enum {
    CONTROLLER_STATE_INIT = 0,
    CONTROLLER_STATE_IDLE,
    CONTROLLER_STATE_PREFLIGHT_CHECK,
    CONTROLLER_STATE_ARMED,
    CONTROLLER_STATE_IGNITION,
    CONTROLLER_STATE_RUNNING,
    CONTROLLER_STATE_SHUTDOWN,
    CONTROLLER_STATE_ERROR
} ControllerState_t;

/**
  * @brief  Controller configuration structure
  */
typedef struct {
    float target_thrust;
    float max_temperature;
    float max_pressure;
    uint32_t run_duration_ms;
} ControllerConfig_t;

/* Controller Initialization and Main Loop */
void Controller_Init(void);
void Controller_Run(void);

/* State Machine Functions */
ControllerState_t Controller_GetState(void);
void Controller_SetState(ControllerState_t new_state);

/* Configuration Functions */
void Controller_SetConfig(const ControllerConfig_t *config);
void Controller_GetConfig(ControllerConfig_t *config);

/* Command Functions */
bool Controller_Arm(void);
bool Controller_Disarm(void);
bool Controller_StartEngine(void);
bool Controller_StopEngine(void);
void Controller_EmergencyShutdown(void);

/* Monitoring Functions */
void Controller_UpdateTelemetry(void);
bool Controller_CheckSystemHealth(void);

#ifdef __cplusplus
}
#endif

#endif /* CONTROLLER_H */
