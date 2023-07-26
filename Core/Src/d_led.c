/**
  ******************************************************************************
  * @file          : d_led.c
  * @brief         : This source code file enables the user to control the
  *                  LED's behavior by setting the appropriate GPIO pins as
  *                  output and configuring their mode, speed, and
  *                  pull-up/pull-down setting.
  ******************************************************************************
  * @attention
  *
  * 
  ******************************************************************************
  */
  
  
/* Includes ------------------------------------------------------------------*/
#include "d_led.h"

/* Global variables ----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static uint32_t redCounterStart = 0;
static uint32_t blueCounterStart = 0;

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  This function blink a LED.
  * @param  port: a pointer to a GPIO port
  * @param  pinSource: a number of pin in a port
  * @retval None
  */
void LED_Blink(GPIO_TypeDef* port, uint16_t pinSource) {
  (PIN_LEVEL(port, pinSource)) ? PIN_L(port, pinSource) : PIN_H(port, pinSource);
}


void BlinkGreen(void) {
  LED_Blink(LED_Port, GREEN_LED);
}


void BlinkRed(uint32_t *millis) {
  uint32_t threshold = 100;
  if (redCounterStart == 0) {
    redCounterStart = *millis;
  } else {
    if (*millis >= (redCounterStart + threshold)) {
      redCounterStart = 0;
      LED_Blink(LED_Port, RED_LED);
    }
  }
}


void BlinkBlue(uint32_t *millis) {
  uint32_t threshold = 500;
  if (blueCounterStart == 0) {
    blueCounterStart = *millis;
  } else {
    if (*millis >= (blueCounterStart + threshold)) {
      blueCounterStart = 0;
      LED_Blink(LED_Port, BLUE_LED);
    }
  }
}
