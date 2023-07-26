/**
  ******************************************************************************
  * @file          : callback.c
  * @brief         : This source code file contains code specifically 
  *                  designed for implementing callback functions calles
  *                  during the whole life cycle.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "callback.h"

/* Private variables ---------------------------------------------------------*/

/* Global variables ----------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Executes a callback
  * @param  callback: A callback pointer
  * @param  addr: Extra arguments structure/array pointer
  * @retval None
  */
void Callback_Handler(void (*callback)(uint32_t*), uint32_t *addr) {
  callback(addr);
}
