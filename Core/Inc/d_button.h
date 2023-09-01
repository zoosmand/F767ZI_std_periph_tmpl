/**
  ******************************************************************************
  * @file          : d_button.h
  * @brief         : Header for d_button.c file.
  *                  The header file provides functions and definitions for
  *                  handling buttons.
  ******************************************************************************
  * @attention
  * 
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUTTON_H
#define __BUTTON_H

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
void BtnPressDown(uint32_t *millis);

/* Private defines -----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif
#endif /*__BUTTON_H */
