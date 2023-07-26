/**
  ******************************************************************************
  * @file          : tim.h
  * @brief         : Header for tim.c file.
  *                  The header file provides functions and definitions for
  *                  configuring timer instances on the STM32F767 
  *                  microcontroller. It includes code for setting up various
  *                  timer parameters such as clock source, prescaler, period,
  *                  and interrupt handling. This file allows developers to
  *                  easily configure and utilize timers for various timing and
  *                  synchronization tasks in their application.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
  /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIM_H
#define __TIM_H

#ifdef __cplusplus
 extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Extern global variables ---------------------------------------------------*/
extern uint32_t _TIMREG_;

/* Exported functions prototypes ---------------------------------------------*/
void BasicTimer_Init(TIM_TypeDef *tim);

/* Private defines -----------------------------------------------------------*/
/*** TIM Registry Flags ***/
#define _BT6IAF_        0 /*!< Basic Timer6 Interrupt Action Flag */


#ifdef __cplusplus
}
#endif
#endif /*__TIM_H */

