/**
  ******************************************************************************
  * @file          : srv_usart.c
  * @brief         : This file provides code for USART service
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "freertos_srv.h"

/* Local variables -----------------------------------------------------------*/
static TaskHandle_t xUsartReceive = NULL;
static TaskHandle_t xUsartSend = NULL;

static uint16_t usartBuf[RXBUF_LEN];
static uint16_t usartBufPtrIn = 0;
static uint16_t usartBufPtrOut = 0;

/* Global variables ----------------------------------------------------------*/

/* Function prototypes */
static void prvUsartReveive(void *pvParameters);
static void prvUsartSend(void *pvParameters);
static uint16_t USART_RxBufferRead(volatile uint8_t*, uint16_t);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Provides FreeRTOS USART data transfer service
  * @return None
  */
void srvUsart(void) {
  xTaskCreate(prvUsartReveive, "USART Recieve", configMINIMAL_STACK_SIZE, NULL, 1, &xUsartReceive);
  xTaskCreate(prvUsartSend, "USART Send", 256, NULL, 1, &xUsartSend);
}


/**
  * @brief  Receives data on USART port 
  * @param pvParameters a prointer to the task parameters 
  * @return None
  */
static void prvUsartReveive(void *pvParameters) {

  while(1) {
    if (FLAG_CHECK(_USARTREG_, _USART_RXAF_)) {

      uint8_t tmp = USART3->RDR;
      uint8_t preRxPtr = usartBufPtrIn - 1;
      preRxPtr &= RXBUF_MASK;

      usartBuf[(usartBufPtrIn++)] = tmp;
      usartBufPtrIn &= RXBUF_MASK;

      // if the buffer is almost full, suspend and let the buffer free by  "prvUsartSend"
      if (usartBufPtrIn == ((usartBufPtrOut - 1) & RXBUF_MASK)) {
        FLAG_SET(_USARTREG_, _USART_LBRRF_);
        vTaskSuspend(NULL);
      }

      // the end of message
      if (tmp == '\r') { // 0x0d
        usartBuf[(usartBufPtrIn++)] = '\n'; // 0x0a
        FLAG_SET(_USARTREG_, _USART_LBRRF_);
      }

      FLAG_CLR(_USARTREG_, _USART_RXAF_);
    }
  }
}


/**
  * @brief  Sends data from fom USART buffer (e.g. print them to the consol)
  * @param pvParameters a prointer to the task parameters 
  * @return None
  */
static void prvUsartSend(void *pvParameters) {
  __IO uint8_t msg[RXBUF_LEN];
  while (1){
    if (FLAG_CHECK(_USARTREG_, _USART_LBRRF_)) {
      uint16_t len = USART_RxBufferRead(msg, RXBUF_LEN);
      printf("%.*s", len, msg);

      FLAG_CLR(_USARTREG_, _USART_LBRRF_);
      vTaskResume(xUsartReceive);
    }
  }
}


/**
 * @brief Copies a payload from USART buffer into another buffer
 * @param buf A buffer to write
 * @param len The length of the passed buffer
 * @retval uint16_t, the length of the payload
*/
static uint16_t USART_RxBufferRead(volatile uint8_t* buf, uint16_t len) {
  uint16_t payloadLen = 0;
  while (usartBufPtrOut != usartBufPtrIn) {
    buf[(payloadLen++)] = usartBuf[(usartBufPtrOut++)];
    usartBufPtrOut &= RXBUF_MASK;
  }
  return payloadLen;
}
