/**
  ******************************************************************************
  * @file           : stm32f4xx.h
  * @brief          : CMSIS STM32F4xx Device Peripheral Access Layer Header File
  ******************************************************************************
  * @attention
  *
  * This is a minimal header file for STM32F4xx devices.
  * For production use, include the official STM32 HAL/CMSIS headers.
  *
  ******************************************************************************
  */

#ifndef STM32F4XX_H
#define STM32F4XX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* FPU Configuration */
#define __FPU_PRESENT             1U
#define __FPU_USED                1U

/**
  * @brief System Control Block (SCB)
  */
typedef struct
{
    volatile uint32_t CPUID;    /* Offset: 0x000 (R/ )  CPUID Base Register */
    volatile uint32_t ICSR;     /* Offset: 0x004 (R/W)  Interrupt Control and State Register */
    volatile uint32_t VTOR;     /* Offset: 0x008 (R/W)  Vector Table Offset Register */
    volatile uint32_t AIRCR;    /* Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
    volatile uint32_t SCR;      /* Offset: 0x010 (R/W)  System Control Register */
    volatile uint32_t CCR;      /* Offset: 0x014 (R/W)  Configuration Control Register */
    volatile uint8_t  SHP[12U]; /* Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
    volatile uint32_t SHCSR;    /* Offset: 0x024 (R/W)  System Handler Control and State Register */
    volatile uint32_t CFSR;     /* Offset: 0x028 (R/W)  Configurable Fault Status Register */
    volatile uint32_t HFSR;     /* Offset: 0x02C (R/W)  HardFault Status Register */
    volatile uint32_t DFSR;     /* Offset: 0x030 (R/W)  Debug Fault Status Register */
    volatile uint32_t MMFAR;    /* Offset: 0x034 (R/W)  MemManage Fault Address Register */
    volatile uint32_t BFAR;     /* Offset: 0x038 (R/W)  BusFault Address Register */
    volatile uint32_t AFSR;     /* Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
    volatile uint32_t PFR[2U];  /* Offset: 0x040 (R/ )  Processor Feature Register */
    volatile uint32_t DFR;      /* Offset: 0x048 (R/ )  Debug Feature Register */
    volatile uint32_t ADR;      /* Offset: 0x04C (R/ )  Auxiliary Feature Register */
    volatile uint32_t MMFR[4U]; /* Offset: 0x050 (R/ )  Memory Model Feature Register */
    volatile uint32_t ISAR[5U]; /* Offset: 0x060 (R/ )  Instruction Set Attributes Register */
    uint32_t RESERVED0[5U];
    volatile uint32_t CPACR;    /* Offset: 0x088 (R/W)  Coprocessor Access Control Register */
} SCB_Type;

/* SCB Base Address */
#define SCS_BASE            (0xE000E000UL)
#define SCB_BASE            (SCS_BASE +  0x0D00UL)
#define SCB                 ((SCB_Type *)SCB_BASE)

/* Interrupt disable/enable */
static inline void __disable_irq(void) { __asm volatile ("cpsid i" : : : "memory"); }
static inline void __enable_irq(void)  { __asm volatile ("cpsie i" : : : "memory"); }

#ifdef __cplusplus
}
#endif

#endif /* STM32F4XX_H */
