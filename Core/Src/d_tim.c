/**
  ******************************************************************************
  * @file          : d_tim.c
  * @brief         : The file contains a set of functions and code snippets
  *                  specifically designed for managing timers on the STM32F767
  *                  microcontroller. It provides a developer with the necessary
  *                  tools to configure, start, stop, and handle interrupts from
  *                  timers. This code file aims to simplify the implementation
  *                  of timer-related functionalities in embedded systems
  *                  development.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "d_tim.h"

/* Private variables ---------------------------------------------------------*/

/* Global variables ----------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  The function is designed to demonstrate the usage of a base timer
  * @param  p: a pointer to a struct that contains parameterss
  * @retval None
  */
void PingTim6(BasicTimerHandlerCallbackParams *p) {
  if (p->tim == TIM6) {
    // blink with the green Led
    // FLAG_SET(_LEDREG_, _LEDGUF_);
    __NOP();
  }
}
