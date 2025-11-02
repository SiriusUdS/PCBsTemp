/**
  ******************************************************************************
  * @file           : controller.c
  * @brief          : Main controller implementation
  ******************************************************************************
  */

#include "controller.h"
#include "engine_interface.h"
#include "hal_init.h"

static ControllerState_t current_state = CONTROLLER_STATE_INIT;
static ControllerConfig_t config = {
    .target_thrust = 1000.0f,      // N
    .max_temperature = 180.0f,      // °C
    .max_pressure = 80.0f,          // bar
    .run_duration_ms = 5000         // 5 seconds
};

static uint32_t state_entry_time = 0;

/**
  * @brief  Initialize the controller
  * @retval None
  */
void Controller_Init(void)
{
    /* Initialize device interface layer */
    EngineInterface_Init();
    
    /* Initialize communication interfaces */
    HAL_UART_Init();
    
    /* Set initial state */
    current_state = CONTROLLER_STATE_IDLE;
}

/**
  * @brief  Main controller run function (called in main loop)
  * @retval None
  */
void Controller_Run(void)
{
    /* Update telemetry */
    Controller_UpdateTelemetry();
    
    /* State machine */
    switch (current_state) {
        case CONTROLLER_STATE_INIT:
            /* Initialization complete, move to idle */
            Controller_SetState(CONTROLLER_STATE_IDLE);
            break;
            
        case CONTROLLER_STATE_IDLE:
            /* Wait for commands */
            /* Check for arm command */
            break;
            
        case CONTROLLER_STATE_PREFLIGHT_CHECK:
            /* Perform preflight checks */
            if (Controller_CheckSystemHealth()) {
                Controller_SetState(CONTROLLER_STATE_ARMED);
            } else {
                Controller_SetState(CONTROLLER_STATE_ERROR);
            }
            break;
            
        case CONTROLLER_STATE_ARMED:
            /* Ready to start engine */
            /* Wait for start command */
            break;
            
        case CONTROLLER_STATE_IGNITION:
            /* Engine ignition sequence */
            EngineInterface_TriggerIgnition();
            Controller_SetState(CONTROLLER_STATE_RUNNING);
            break;
            
        case CONTROLLER_STATE_RUNNING:
            /* Engine running - monitor and control */
            if (!Controller_CheckSystemHealth()) {
                Controller_EmergencyShutdown();
            }
            
            /* Check for run duration timeout */
            /* Implement throttle control based on target thrust */
            break;
            
        case CONTROLLER_STATE_SHUTDOWN:
            /* Shutdown sequence */
            EngineInterface_Stop();
            Controller_SetState(CONTROLLER_STATE_IDLE);
            break;
            
        case CONTROLLER_STATE_ERROR:
            /* Error state - perform safe shutdown */
            EngineInterface_Stop();
            break;
            
        default:
            Controller_SetState(CONTROLLER_STATE_ERROR);
            break;
    }
}

/**
  * @brief  Get current controller state
  * @retval Current state
  */
ControllerState_t Controller_GetState(void)
{
    return current_state;
}

/**
  * @brief  Set controller state
  * @param  new_state: New state to transition to
  * @retval None
  */
void Controller_SetState(ControllerState_t new_state)
{
    current_state = new_state;
    state_entry_time = 0; // Update with system timer
}

/**
  * @brief  Set controller configuration
  * @param  config: Pointer to configuration structure
  * @retval None
  */
void Controller_SetConfig(const ControllerConfig_t *new_config)
{
    if (new_config != NULL) {
        config = *new_config;
    }
}

/**
  * @brief  Get controller configuration
  * @param  config: Pointer to configuration structure
  * @retval None
  */
void Controller_GetConfig(ControllerConfig_t *out_config)
{
    if (out_config != NULL) {
        *out_config = config;
    }
}

/**
  * @brief  Arm the controller
  * @retval true if successful, false otherwise
  */
bool Controller_Arm(void)
{
    if (current_state == CONTROLLER_STATE_IDLE) {
        Controller_SetState(CONTROLLER_STATE_PREFLIGHT_CHECK);
        return true;
    }
    return false;
}

/**
  * @brief  Disarm the controller
  * @retval true if successful, false otherwise
  */
bool Controller_Disarm(void)
{
    if (current_state == CONTROLLER_STATE_ARMED) {
        Controller_SetState(CONTROLLER_STATE_IDLE);
        return true;
    }
    return false;
}

/**
  * @brief  Start the engine
  * @retval true if successful, false otherwise
  */
bool Controller_StartEngine(void)
{
    if (current_state == CONTROLLER_STATE_ARMED) {
        EngineInterface_Start();
        Controller_SetState(CONTROLLER_STATE_IGNITION);
        return true;
    }
    return false;
}

/**
  * @brief  Stop the engine
  * @retval true if successful, false otherwise
  */
bool Controller_StopEngine(void)
{
    if (current_state == CONTROLLER_STATE_RUNNING) {
        Controller_SetState(CONTROLLER_STATE_SHUTDOWN);
        return true;
    }
    return false;
}

/**
  * @brief  Emergency shutdown
  * @retval None
  */
void Controller_EmergencyShutdown(void)
{
    EngineInterface_Stop();
    Controller_SetState(CONTROLLER_STATE_ERROR);
}

/**
  * @brief  Update telemetry data
  * @retval None
  */
void Controller_UpdateTelemetry(void)
{
    EngineParams_t params;
    EngineInterface_GetParameters(&params);
    
    /* Send telemetry over UART or other interface */
    /* Log data to storage if available */
}

/**
  * @brief  Check system health
  * @retval true if healthy, false otherwise
  */
bool Controller_CheckSystemHealth(void)
{
    /* Check safety conditions through device interface */
    if (!EngineInterface_CheckSafety()) {
        return false;
    }
    
    /* Check engine parameters */
    EngineParams_t params;
    EngineInterface_GetParameters(&params);
    
    if (params.chamber_temperature > config.max_temperature) {
        return false;
    }
    
    if (params.chamber_pressure > config.max_pressure) {
        return false;
    }
    
    /* All checks passed */
    return true;
}
