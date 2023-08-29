/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the defines of the application.
  ******************************************************************************
  * @attention
  *
  * 
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/*** Define debug output to SWO ***/
// #define SWO_ITM
#define SWO_USART

/*** Full assert ***/
#define USE_FULL_ASSERT

#ifdef __cplusplus
extern "C" {
#endif

#define DEBUG

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

/* Private includes ----------------------------------------------------------*/
#include "stm32f7xx.h"
#include "common.h"
#include "stm32f7xx_it.h"
#include "callback.h"
#include "usart.h"
#include "tim.h"
#include "led.h"
/*** FreeRTOS Services ***/
#include "freertos_srv.h"


/* Exported types ------------------------------------------------------------*/
struct __FILE {
  int handle;
  /* Whatever you require here. If the only file you are using is */
  /* standard output using printf() for debugging, no file handling */
  /* is required. */
};

/**
  * @brief  RCC Clocks Frequency Structure
  */
typedef struct {
  uint32_t HCLK_Freq;          /*!< HCLK clock frequency */
  uint32_t PCLK1_Freq;         /*!< PCLK1 clock frequency */
  uint32_t PCLK1_Freq_Tim;     /*!< PCLK1 clock frequency for timers */
  uint32_t PCLK2_Freq;         /*!< PCLK2 clock frequency */
  uint32_t PCLK2_Freq_Tim;     /*!< PCLK2 clock frequency for timers */
  uint32_t PLLQ_Freq;          /*!< PLLQ clock frequency for USB bus */
} RCC_ClocksTypeDef;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Extern global variables ---------------------------------------------------*/
extern uint32_t SystemCoreClock;
extern RCC_ClocksTypeDef RccClocks;

/* Exported functions prototypes ---------------------------------------------*/
extern void _Delay(uint32_t delay);

/* Private defines -----------------------------------------------------------*/

#define CCMRAM  __attribute__((section(".ccmram")))


#ifdef __cplusplus
}
#endif
#endif /* __MAIN_H */
