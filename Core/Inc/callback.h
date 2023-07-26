/**
  ******************************************************************************
  * @file          : callback.h
  * @brief         : Header for callback.c file.
  *                  The header file contains the necessary function prototypes
  *                  and definitions for the implementation of callback
  *                  functionality in the "callback.c" source file.
  ******************************************************************************
  * @attention
  *
  * 
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CALLBACK_H
#define __CALLBACK_H

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
void Callback_Handler(void (*callback)(uint32_t*), uint32_t *addr);

/* Private defines -----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif
#endif /*__CALLBACK_H */

