/**
  ******************************************************************************
  * @file          : srv_led.c
  * @brief         : This file provides code for FreeRTOS LED service
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "freertos_srv.h"

/* Local variables -----------------------------------------------------------*/
static TaskHandle_t xLedIndication = NULL;

static void prvLedOnTimerIndtcation(void *pvParameters);
static void prvLedOnUsartIndtcation(void *pvParameters);

/* Global variables ----------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/
static void LED_Blink(GPIO_TypeDef*, uint16_t);
static void BlinkGreen(void);
static void BlinkRed(void);
static void BlinkBlue(void);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Provides FreeRTOS LED service.
  * @return None
  */
void srvLed(void) {
  xTaskCreate(prvLedOnTimerIndtcation, "LED Indicator", configMINIMAL_STACK_SIZE, NULL, 1, &xLedIndication);
  xTaskCreate(prvLedOnUsartIndtcation, "LED Indicator", configMINIMAL_STACK_SIZE, NULL, 1, &xLedIndication);
}


/**
  * @brief  LED Indication
  * @return None
  */
static void prvLedOnTimerIndtcation(void *pvParameters) {

  while (1) {
    if (FLAG_CHECK(_TIMREG_, _BT6IAF_)) {
      FLAG_CLR(_TIMREG_, _BT6IAF_);
      BlinkGreen();
    }
    if (FLAG_CHECK(_EXTIREG_, _BTN0DF_)) {
      FLAG_CLR(_EXTIREG_, _BTN0DF_);
      BlinkRed();
    }
  }
}



/**
  * @brief  LED Indication
  * @return None
  */
static void prvLedOnUsartIndtcation(void *pvParameters) {

  while (1) {
    if (FLAG_CHECK(_USARTREG_, _USART_RXAF_)) {
      BlinkBlue();
      vTaskDelay(10);
      BlinkBlue();
    }
  }
}



/* Private functions ---------------------------------------------------------*/
/**
  * @brief  This function blink a LED.
  * @param  port: a pointer to a GPIO port
  * @param  pinSource: a number of pin in a port
  * @retval None
  */
static void LED_Blink(GPIO_TypeDef* port, uint16_t pinSource) {
  (PIN_LEVEL(port, pinSource)) ? PIN_L(port, pinSource) : PIN_H(port, pinSource);
}


static void BlinkGreen(void) {
  LED_Blink(LED_Port, GREEN_LED);
}


static void BlinkRed(void) {
  LED_Blink(LED_Port, RED_LED);
}


static void BlinkBlue(void) {
  LED_Blink(LED_Port, BLUE_LED);
}
