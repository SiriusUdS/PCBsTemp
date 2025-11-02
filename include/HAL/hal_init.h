/**
  ******************************************************************************
  * @file           : hal_init.h
  * @brief          : HAL initialization header
  ******************************************************************************
  * @attention
  *
  * Hardware Abstraction Layer (HAL) - Lowest level interface to hardware
  * This layer provides direct access to STM32 peripherals
  *
  ******************************************************************************
  */

#ifndef HAL_INIT_H
#define HAL_INIT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
  * @brief  HAL Status structures definition
  */
typedef enum
{
    HAL_OK       = 0x00U,
    HAL_ERROR    = 0x01U,
    HAL_BUSY     = 0x02U,
    HAL_TIMEOUT  = 0x03U
} HAL_StatusTypeDef;

/* HAL Initialization Functions */
void HAL_Init(void);
void HAL_MspInit(void);
void SystemClock_Config(void);

/* GPIO HAL Functions */
void HAL_GPIO_Init(void);
void HAL_GPIO_WritePin(uint32_t port, uint16_t pin, uint8_t state);
uint8_t HAL_GPIO_ReadPin(uint32_t port, uint16_t pin);

/* Timer HAL Functions */
void HAL_TIM_Init(void);
void HAL_TIM_Start(void);

/* ADC HAL Functions */
void HAL_ADC_Init(void);
uint16_t HAL_ADC_Read(uint8_t channel);

/* UART HAL Functions */
void HAL_UART_Init(void);
HAL_StatusTypeDef HAL_UART_Transmit(uint8_t *data, uint16_t size, uint32_t timeout);
HAL_StatusTypeDef HAL_UART_Receive(uint8_t *data, uint16_t size, uint32_t timeout);

#ifdef __cplusplus
}
#endif

#endif /* HAL_INIT_H */
