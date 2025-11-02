/**
  ******************************************************************************
  * @file           : sensors.h
  * @brief          : Sensor components header
  ******************************************************************************
  * @attention
  *
  * Components Layer - Hardware component drivers
  * This layer provides drivers for specific hardware components like
  * sensors, actuators, communication modules, etc.
  *
  ******************************************************************************
  */

#ifndef SENSORS_H
#define SENSORS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
  * @brief  Sensor data structure
  */
typedef struct {
    float temperature;
    float pressure;
    float flow_rate;
    uint32_t timestamp;
} SensorData_t;

/* Sensor Initialization */
void Sensors_Init(void);

/* Temperature Sensor Functions */
float Sensors_ReadTemperature(uint8_t sensor_id);

/* Pressure Sensor Functions */
float Sensors_ReadPressure(uint8_t sensor_id);

/* Flow Rate Sensor Functions */
float Sensors_ReadFlowRate(uint8_t sensor_id);

/* Get all sensor data */
void Sensors_GetData(SensorData_t *data);

#ifdef __cplusplus
}
#endif

#endif /* SENSORS_H */
