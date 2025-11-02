/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body for STM32 Rocket Engine Control
  ******************************************************************************
  * @attention
  *
  * This is a template project for STM32 embedded development.
  * Customize this file according to your application requirements.
  *
  ******************************************************************************
  */

#include "stm32f4xx.h"
#include "hal_init.h"
#include "controller.h"

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    /* Initialize the HAL Library */
    HAL_Init();
    
    /* Initialize all configured peripherals */
    Controller_Init();
    
    /* Infinite loop */
    while (1)
    {
        /* Main application loop */
        Controller_Run();
    }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* User can add his own implementation to report the error */
    __disable_irq();
    while (1)
    {
        /* Stay here in case of error */
    }
}

/* Minimal system initialization stub */
void SystemInit(void)
{
    /* FPU settings - Enable FPU if used */
    #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
        SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */
    #endif
}
