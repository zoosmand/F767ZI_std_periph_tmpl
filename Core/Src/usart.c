/**
  ******************************************************************************
  * @file          : usart.c
  * @brief         : This source code file contains code specifically to
  *                  configure the USART instances on the STM32F767
  *                  microcontroller. This file includes functions and
  *                  definitions that allow the user to set up the USART
  *                  communication parameters such as baud rate, data bits,
  *                  parity, and stop bits. It also provides functions to enable
  *                  and disable the USART, as well as to transmit and receive
  *                  data using the USART interface.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* Private variables ---------------------------------------------------------*/

/* Global variables ----------------------------------------------------------*/
uint32_t _USARTREG_ = 0;


/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Initializes the USART peripheral on the STM32F767 microcontroller,
  *         allowing for communication with external devices using the USART
  *         protocol.
  * @param  usart An USART definition struct 
  * @retval None
  */
void USART_Init(USART_TypeDef* usart) {

  if (usart == USART3) {
    /** USART3 GPIO Configuration
      PD8    ------> USART3_TX
      PD9    ------> USART3_RX
    */
#define USART_3_MASK  (USART_3_TX_Pin_Mask | USART_3_RX_Pin_Mask)

    MODIFY_REG(USART_3_Port->MODER, USART_3_MASK, (
      (_MODE_AF << (USART_3_TX_Pin_Pos * 2))
      | (_MODE_AF << (USART_3_RX_Pin_Pos * 2))
      ));
    MODIFY_REG(USART_3_Port->OSPEEDR, USART_3_MASK, (
      (_SPEED_V << (USART_3_TX_Pin_Pos * 2))
      | (_SPEED_V << (USART_3_RX_Pin_Pos * 2))
      ));
    MODIFY_REG(USART_3_Port->AFR[1], 0x00000ff0, (
      (GPIO_AF_7 << ((USART_3_TX_Pin_Pos - 8) * 4))
      | (GPIO_AF_7 << ((USART_3_RX_Pin_Pos - 8) * 4))
      ));

    /* Transmit enable */
    PREG_SET(USART3->CR1, USART_CR1_TE_Pos);
    /* Receive enable */
    PREG_SET(USART3->CR1, USART_CR1_RE_Pos);
    /* Asyncronos mode */
    CLEAR_BIT(USART3->CR2, (USART_CR2_LINEN | USART_CR2_CLKEN));
    CLEAR_BIT(USART3->CR3, (USART_CR3_SCEN | USART_CR3_IREN | USART_CR3_HDSEL));
    /* Set Baudrate */
    USART3->BRR = BRR_Value;
    /* Enable RXNE Interrupt */
    PREG_SET(USART3->CR1, USART_CR1_RXNEIE_Pos);
    /* Enable USART3 */
    PREG_SET(USART3->CR1, USART_CR1_UE_Pos);

    /* USART3 interrupt Init */
    // NVIC_SetPriority(USART3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 15, 0));
    // NVIC_EnableIRQ(USART3_IRQn);
    /* Clear RXNE  pernding bit */
    PREG_SET(USART3->RQR, USART_RQR_RXFRQ_Pos);

  }
  else {
    // None of USARTs initialization
    Error_Handler();
  }
}
