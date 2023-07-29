/**
  ******************************************************************************
  * File Name          : srv_logger.c
  * Description        : This file provides code for FreeRTOS Logger service
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "freertos_srv.h"

/* Local variables -----------------------------------------------------------*/
static TaskHandle_t xPeriodicLogMessage = NULL;


/* Function prototypes */
static void prvPeriodicLogMessage(void *pvParameters);





/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/**
  * @brief  Provides FreeRTOS Logger service.
  * @return None
  */
void srvLogger(void) {

  xTaskCreate(prvPeriodicLogMessage, "PeriodicLogMessage", configMINIMAL_STACK_SIZE, NULL, 1, &xPeriodicLogMessage);
}


/**
  * @brief  Sends a message to a log representer.
  * @return None
  */
static void prvPeriodicLogMessage(void *pvParameters) {

  while(1) {
    vTaskDelay(1000);
  
    printf("test\n");
  }
}

/*************************** © Zoo IPS, 2021 **********************************/
