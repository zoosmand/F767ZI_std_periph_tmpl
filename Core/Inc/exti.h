/**
  ******************************************************************************
  * @file          : led.h
  * @brief         : Header for led.c file.
  *                  The header file provides functions and definitions for
  *                  configuring the GPIO instances on the STM32F767 
  *                  microcontroller specifically for LED indication. It 
  *                  includes code for setting up the necessary pins, 
  *                  enabling or disabling the LED's, and controlling their
  *                  states. This file allows developers to easily configure
  *                  the GPIOs for LED indication in their applications.
  ******************************************************************************
  * @attention
  * 
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EXTI_H
#define __EXTI_H

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
extern uint32_t _EXTIREG_;

/* Exported functions prototypes ---------------------------------------------*/
void EXTI_Init(void);

/* Private defines -----------------------------------------------------------*/
#define BTN0_Pin        GPIO_PIN_13
#define BTN0_Pin_Pos    GPIO_PIN_13_Pos
#define BTN0_Pin_Mask   GPIO_PIN_13_Mask
#define BTN0_Port       GPIOC
/*** EXTI Registry Flags ***/
#define _BTN0DF_        0 /*!< Button0 is Down Flag */
#define _BTN0UF_        1 /*!< Button0 is Up Flag */
#define _BTN0PDF_       2 /*!< Button0 Press Down Flag */
#define _BTN0CLF_       3 /*!< Button0 CLick Flag */
#define _BTN0ONCLF_     4 /*!< Button0 OnCLick Flag */
#define _BTN0ONLCL2SF_  5 /*!< Button0 OnLongCLick 2sec Flag */
#define _BTN0ONLCL4SF_  6 /*!< Button0 OnLongCLick 4sec Flag */
#define _BTN0ONLCL8SF_  7 /*!< Button0 OnLongCLick 8sec Flag */


#ifdef __cplusplus
}
#endif
#endif /*__EXTI_H */
