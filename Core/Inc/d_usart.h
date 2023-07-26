/**
  ******************************************************************************
  * @file          : d_usart.h
  * @brief         : Header for d_usart.c file
  *                  The header file contains the code specifically designed
  *                  for USART (Universal Synchronous/Asynchronous
  *                  Receiver/Transmitter) communication on the STM32F767
  *                  microcontroller.
  ******************************************************************************
  * @attention
  *
  * 
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __D_USART_H
#define __D_USART_H

#ifdef __cplusplus
 extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef struct {
  USART_TypeDef   *usart;           /*!< Parameter */
} UsartHandlerCallbackParams;       /*!< USART callback parameters struckt */

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Extern global variables ---------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void EchoToUSART(void);
void UsartToBuffer(UsartHandlerCallbackParams* p);
uint16_t USART_RxBufferRead(volatile uint8_t *buf, uint16_t len);

/* Private defines -----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif
#endif /*__D_USART_H */

