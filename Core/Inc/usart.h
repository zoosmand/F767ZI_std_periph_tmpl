/**
  ******************************************************************************
  * @file          : usart.h
  * @brief         : Header for usart.c file.
  *                  The header file provides functions and definitions for
  *                  configuring USART instances on the STM32F767
  *                  microcontroller. It includes code for setting up the USART
  *                  communication parameters such as baud rate, data bits,
  *                  parity, and stop bits. Additionally, it provides functions
  *                  for enabling and disabling the USART, as well as
  *                  transmitting and receiving data.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __USART_H
#define __USART_H

#ifdef __cplusplus
 extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#define BAUDRATE            115200
#define BRR_Value           (RccClocks.PCLK1_Freq / BAUDRATE)

/* Extern global variables ---------------------------------------------------*/
extern uint32_t _USARTREG_;

/* Exported functions prototypes ---------------------------------------------*/
void USART_Init(USART_TypeDef *usart);

/* Private defines -----------------------------------------------------------*/
#define USART_3_TX_Pin              GPIO_PIN_8
#define USART_3_TX_Pin_Pos          GPIO_PIN_8_Pos
#define USART_3_TX_Pin_Mask         GPIO_PIN_8_Mask
#define USART_3_RX_Pin              GPIO_PIN_9
#define USART_3_RX_Pin_Pos          GPIO_PIN_9_Pos
#define USART_3_RX_Pin_Mask         GPIO_PIN_9_Mask
#define USART_3_Port                GPIOD
/*** RX Buffer definition ***/
#define USART_BUFFER_LEN            32
#define USART_BUFFER_ITEM_SIZE      sizeof(uint8_t)
/*** USART Registry Flags ***/
#define _USART_LBRRF_               0 /*!< USART Local Buffer Ready To Read Flag */
#define _USART_RXAF_                1 /*!< RX Action Flag */


#ifdef __cplusplus
}
#endif
#endif /*__ USART_H */

