/**
  ******************************************************************************
  * @file          : d_usart.c
  * @brief         : This C code file is dedicated to USART (Universal
  *                  Synchronous/Asynchronous Receiver/Transmitter)
  *                  functionality and contains developer code for implementing
  *                  USART communication on the STM32F767 microcontroller.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "callback.h"

/* Private variables ---------------------------------------------------------*/
static uint16_t usartBuf[RXBUF_LEN];
static uint16_t usartBufPtrIn = 0;
static uint16_t usartBufPtrOut = 0;








////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Echoes to the previously selected USART port
*/
void EchoToUSART(void) {
  __IO uint8_t msg[RXBUF_LEN];
  uint16_t len = USART_RxBufferRead(msg, RXBUF_LEN);
  printf("%.*s", len, msg);
}


/**
  * @brief  Reads USART DR redister and writes the content to buffer
  * @param  usart peripheral struct
  * @retval None
 */
void UsartToBuffer(UsartHandlerCallbackParams* p) {
  uint8_t tmp = p->usart->RDR;
  uint8_t preRxPtr = usartBufPtrIn - 1;
  preRxPtr &= RXBUF_MASK;

  usartBuf[(usartBufPtrIn++)] = tmp;
  usartBufPtrIn &= RXBUF_MASK;

  // the end of message
  if (tmp == '\r') { // 0x0d
    usartBuf[(usartBufPtrIn++)] = '\n'; // 0x0a
    FLAG_SET(_USARTREG_, _USART_LBRRF_);
  }
}


/**
 * @brief Copies a payload from USART buffer into another buffer
 * @param buf A buffer to write
 * @param len The length of the passed buffer
 * @retval uint16_t, the length of the payload
*/
uint16_t USART_RxBufferRead(volatile uint8_t* buf, uint16_t len) {
  uint16_t payloadLen = 0;
  while (usartBufPtrOut != usartBufPtrIn) {
    buf[(payloadLen++)] = usartBuf[(usartBufPtrOut++)];
    usartBufPtrOut &= RXBUF_MASK;
  }
  return payloadLen;
}
