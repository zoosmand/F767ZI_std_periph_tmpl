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
#include "exti.h"

/* Global variables ----------------------------------------------------------*/
uint32_t _EXTIREG_ = 0;

/* Private variables ---------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
void EXTI_Init(void) {
  /*** GPIO Button -  PC15 ***/
  /* Mode */
  // MODIFY_REG(BTN0_Port->MODER, BTN0_Pin_Mask, (_MODE_IN << BTN0_Pin_Pos * 2));
  /* Speed */
  // MODIFY_REG(GPIOG->OSPEEDR, (LED0_Pin_Mask | LED1_Pin_Mask | LED2_Pin_Mask), ((_SPEED_L << LED0_Pin_Pos * 2) | (_SPEED_L << LED1_Pin_Pos * 2) | (_SPEED_L << LED2_Pin_Pos * 2)));
  /* Output type */
  // MODIFY_REG(GPIOG->OTYPER, ((_OTYPE_PP << LED0_Pin_Pos) | (_OTYPE_PP << LED1_Pin_Pos) | (_OTYPE_PP << LED2_Pin_Pos)), ((_OTYPE_PP << LED0_Pin_Pos) | (_OTYPE_PP << LED1_Pin_Pos) | (_OTYPE_PP << LED2_Pin_Pos)));
  /* Push mode */
  // MODIFY_REG(BTN0_Port->PUPDR, BTN0_Pin_Mask, (_PUPD_NO << BTN0_Pin_Pos * 2));

  PREG_SET(EXTI->IMR, EXTI_IMR_MR13_Pos);
  PREG_SET(EXTI->FTSR, EXTI_FTSR_TR13_Pos);

  /* EXTI Line 10-15 interrupt Init */
  NVIC_SetPriority(EXTI15_10_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 15, 0));
  NVIC_EnableIRQ(EXTI15_10_IRQn);

}
