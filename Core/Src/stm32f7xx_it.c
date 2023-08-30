/**
  ******************************************************************************
  * @file    stm32f7xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * 
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_it.h"
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

/* External variables --------------------------------------------------------*/

/******************************************************************************/
/*           Cortex-M7 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void) {
  //
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void) {
  Error_Handler();
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void) {
  Error_Handler();
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void) {
  Error_Handler();
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void) {
  Error_Handler();
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void) {
  //
}

/******************************************************************************/
/* STM32F7xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f7xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles FLASH global interrupt.
  */
void FLASH_IRQHandler(void) {
  //
}

/**
  * @brief This function handles RCC global interrupt.
  */
void RCC_IRQHandler(void) {
  //
}

/**
  * @brief This function handles USART3 global interrupt.
  */
void USART3_IRQHandler(void) {
  /* Clear RXNE bit */
  PREG_SET(USART3->RQR, USART_RQR_RXFRQ_Pos);
  __NOP();
  FLAG_SET(_USARTREG_, _USART_RXAF_);
}

/**
  * @brief This function handles EXTI lines from 10 to 15 global interrupt.
  */
void EXTI15_10_IRQHandler(void) {
  /* Clear perding bit */
  if (READ_BIT(EXTI->PR, EXTI_PR_PR13) == (EXTI_PR_PR13)) {
    PREG_SET(EXTI->PR, EXTI_PR_PR13_Pos);
    __NOP();
    FLAG_SET(_EXTIREG_, _BTN0DF_);
  }
}

/**
  * @brief This function handles TIM6 global interrupt.
  */
void TIM6_DAC_IRQHandler(void) {
  PREG_CLR(TIM6->SR, TIM_SR_UIF_Pos);
  __NOP();
  FLAG_SET(_TIMREG_, _BT6IAF_);
}
