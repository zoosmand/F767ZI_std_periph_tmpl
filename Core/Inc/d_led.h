/**
  ******************************************************************************
  * @file          : d_led.h
  * @brief         : This file provides code contains code specifically
  *                  designed for controlling GPIO LEDs on the STM32F767
  *                  microcontroller. It includes functions and definitions
  *                  necessary for manipulating the LED pins, allowing for easy
  *                  control and customization of LED behavior
  ******************************************************************************
  * @attention
  *
  * 
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __D_LED_H
#define __D_LED_H


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

/* Exported functions prototypes ---------------------------------------------*/
void LED_Blink(GPIO_TypeDef* port, uint16_t pinSource);
//
void BlinkGreen(uint32_t *millis);
void BlinkRed(void);
void BlinkBlue(uint32_t *millis);

/* Private defines -----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif
#endif /*__D_LED_H */
