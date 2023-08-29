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

/* Local definitions ---------------------------------------------------------*/
#define RECEIVE_BUFFER_SIZE USART_BUFFER_LEN
#define QTX_TIMEOUT (TickType_t)0
#define QRX_TIMEOUT (TickType_t)0

/* Local variables -----------------------------------------------------------*/
static TaskHandle_t xUsartReceive = NULL;
static TaskHandle_t xUsartSend = NULL;
static QueueHandle_t xUsartBuffer = NULL;

/* Global variables ----------------------------------------------------------*/

/* Function prototypes */
static void prvUsartReceive(void *pvParameters);
static void prvUsartSend(void *pvParameters);
static uint16_t USART_RxBufferRead(volatile uint8_t*, uint16_t);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Provides FreeRTOS USART data transfer service
  * @return None
  */
void srvUsart(void) {
  xTaskCreate(prvUsartReceive, "USART Recieve", configMINIMAL_STACK_SIZE, NULL, 1, &xUsartReceive);
  xTaskCreate(prvUsartSend, "USART Send", configMINIMAL_STACK_SIZE, NULL, 1, &xUsartSend);

  xUsartBuffer = xQueueCreate(USART_BUFFER_LEN, USART_BUFFER_ITEM_SIZE); 
  configASSERT(xUsartBuffer);
}


/**
  * @brief  Receives data on USART port 
  * @param pvParameters a prointer to the task parameters 
  * @return None
  */
static void prvUsartReceive(void *pvParameters) {

  static uint8_t tmp = 0;
  const static uint8_t tmp_n = '\n';

  while(1) {
    if (FLAG_CHECK(_USARTREG_, _USART_RXAF_)) {

      // if the buffer is almost full, suspend and let the buffer free by  "prvUsartSend"
      if ((USART_BUFFER_LEN - uxQueueSpacesAvailable(xUsartBuffer)) <= 1) {
        FLAG_SET(_USARTREG_, _USART_LBRRF_);
        vTaskSuspend(NULL);
      }

      tmp = USART3->RDR;
      if (xQueueSend(xUsartBuffer, &tmp, QTX_TIMEOUT) != pdPASS) {
        Error_Handler();
      }

      // at the end of message add '\n'
      if (tmp == '\r') { // 0x0d
        if (xQueueSend(xUsartBuffer, &tmp_n, QTX_TIMEOUT) == pdPASS) {
          FLAG_SET(_USARTREG_, _USART_LBRRF_);
        } else {
          Error_Handler();
        }
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

  __IO uint8_t msg[RECEIVE_BUFFER_SIZE];
  while (1){
    if (FLAG_CHECK(_USARTREG_, _USART_LBRRF_)) {
      uint16_t len = USART_RxBufferRead(msg, USART_BUFFER_LEN);

      // printf will not display any symbol until the "\n" comes
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
  uint8_t tmp = 0;
  while ((USART_BUFFER_LEN - uxQueueSpacesAvailable(xUsartBuffer)) > 0) {
    if (xQueueReceive(xUsartBuffer, &tmp, QRX_TIMEOUT) == pdPASS) {
      buf[(payloadLen++)] = tmp; 
    } else {
      Error_Handler();
    }
  }
  return payloadLen;
}
