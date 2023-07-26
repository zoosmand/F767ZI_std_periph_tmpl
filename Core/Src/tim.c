/**
  ******************************************************************************
  * @file          : tim.c
  * @brief         : The file contains the necessary code for configuring timer
  *                  instances on the STM32F767 microcontroller. This code file
  *                  provides functions and settings to initialize and configure
  *                  timers, allowing for precise timing and synchronization in
  *                  various applications.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/* Private variables ---------------------------------------------------------*/

/* Global variables ----------------------------------------------------------*/
uint32_t _TIMREG_ = 0;

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Initialises a basic timer
  * @param  tim The basic timer struct
  * @retval None
  */
void BasicTimer_Init(TIM_TypeDef *tim) {

  if (tim == TIM6) {
    /* TIM6 interrupt Init */
    NVIC_SetPriority(TIM6_DAC_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 15, 0));
    NVIC_EnableIRQ(TIM6_DAC_IRQn);

    TIM6->PSC = 54000U - 1U; // APB1 runs on max freq of SystemCoreClock/2
    TIM6->ARR = 2000U - 1U;
    /* Autoreload enable */ 
    PREG_SET(TIM6->CR1, TIM_CR1_ARPE_Pos);

    /* Interrupt enabling passes */
    PREG_CLR(TIM6->SR, TIM_SR_UIF_Pos);
    PREG_SET(TIM6->DIER, TIM_DIER_UIE_Pos);
    PREG_SET(TIM6->CR1, TIM_CR1_CEN_Pos);
  } else {
    // None of timers initialization
    Error_Handler();
  }
}

