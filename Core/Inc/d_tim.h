/**
  ******************************************************************************
  * @file          : d_tim.h
  * @brief         : Header for d_tim.c file.
  *                  The header file provides a collection of functions and
  *                  definitions specifically designed for timers, allowing
  *                  developers to easily incorporate timer functionality into
  *                  their code on the STM32F767 microcontroller.
  ******************************************************************************
  * @attention
  *
  * 
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef __D_TIM_H
#define __D_TIM_H

#ifdef __cplusplus
 extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef struct {
  TIM_TypeDef   *tim;               /*!< Parameter */
} BasicTimerHandlerCallbackParams;  /*!< Timer callback parameters struckt */

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Extern global variables ---------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void PingTim6(BasicTimerHandlerCallbackParams *p);

/* Private defines -----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif
#endif /*__D_TIM_H */

