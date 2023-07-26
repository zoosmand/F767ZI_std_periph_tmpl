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
#ifndef __LED_H
#define __LED_H

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
extern uint32_t _LEDREG_;

/* Exported functions prototypes ---------------------------------------------*/
void LED_Init(void);

/* Private defines -----------------------------------------------------------*/
#define LED0_Pin        GPIO_PIN_0
#define LED0_Pin_Pos    GPIO_PIN_0_Pos
#define LED0_Pin_Mask   GPIO_PIN_0_Mask
#define LED1_Pin        GPIO_PIN_7
#define LED1_Pin_Pos    GPIO_PIN_7_Pos
#define LED1_Pin_Mask   GPIO_PIN_7_Mask
#define LED2_Pin        GPIO_PIN_14
#define LED2_Pin_Pos    GPIO_PIN_14_Pos
#define LED2_Pin_Mask   GPIO_PIN_14_Mask
#define LED_Port        GPIOB
#define GREEN_LED       LED0_Pin
#define BLUE_LED        LED1_Pin
#define RED_LED         LED2_Pin
/*** LED Registry Flags ***/
#define _LEDGUF_     0 /*!< LED Green Up Flag */
#define _LEDBUF_     1 /*!< LED Blue Up Flag */
#define _LEDRUF_     2 /*!< LED Red Up Flag */


#ifdef __cplusplus
}
#endif
#endif /*__LED_H */
