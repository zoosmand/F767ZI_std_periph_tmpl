/**
  ******************************************************************************
  * @file          : led.c
  * @brief         : This source code file contains the necessary code to 
  *                  configure the GPIO instances for LED indication on the
  *                  STM32F767 microcontroller.
  ******************************************************************************
  * @attention
  *
  * 
  ******************************************************************************
  */
  
  
/* Includes ------------------------------------------------------------------*/
#include "led.h"

/* Global variables ----------------------------------------------------------*/
uint32_t _LEDREG_ = 0;

/* Private variables ---------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
void LED_Init(void) {
  /*** GPIO LED -  PB0, PB7, PB14 ***/
  /* Mode */
  MODIFY_REG(LED_Port->MODER, (LED0_Pin_Mask | LED1_Pin_Mask | LED2_Pin_Mask), ((_MODE_OUT << LED0_Pin_Pos * 2) | (_MODE_OUT << LED1_Pin_Pos * 2) | (_MODE_OUT << LED2_Pin_Pos * 2)));
  /* Speed */
  // MODIFY_REG(GPIOG->OSPEEDR, (LED0_Pin_Mask | LED1_Pin_Mask | LED2_Pin_Mask), ((_SPEED_L << LED0_Pin_Pos * 2) | (_SPEED_L << LED1_Pin_Pos * 2) | (_SPEED_L << LED2_Pin_Pos * 2)));
  /* Output type */
  // MODIFY_REG(GPIOG->OTYPER, ((_OTYPE_PP << LED0_Pin_Pos) | (_OTYPE_PP << LED1_Pin_Pos) | (_OTYPE_PP << LED2_Pin_Pos)), ((_OTYPE_PP << LED0_Pin_Pos) | (_OTYPE_PP << LED1_Pin_Pos) | (_OTYPE_PP << LED2_Pin_Pos)));
  /* Push mode */
  // MODIFY_REG(GPIOG->PUPDR, (LED0_Pin_Mask | LED1_Pin_Mask | LED2_Pin_Mask), ((_PUPD_NO << LED0_Pin_Pos * 2) | (_PUPD_NO << LED1_Pin_Pos * 2) | (_PUPD_NO << LED2_Pin_Pos * 2)));
}
