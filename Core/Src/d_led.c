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
static uint32_t greenCounterStart = 0;
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


void BlinkGreen(uint32_t *millis) {
  uint32_t threshold = 100;
  if (greenCounterStart == 0) {
    greenCounterStart = *millis;
  } else {
    if (*millis >= (greenCounterStart + threshold)) {
      greenCounterStart = 0;
      LED_Blink(LED_Port, GREEN_LED);
    }
  }
}


void BlinkRed(void) {
  LED_Blink(LED_Port, RED_LED);
}


void BlinkBlue(uint32_t *millis) {
  uint32_t threshold = 10;
  if (blueCounterStart == 0) {
    blueCounterStart = *millis;
    LED_Blink(LED_Port, BLUE_LED);
  } else {
    if (*millis >= (blueCounterStart + threshold)) {
      blueCounterStart = 0;
      LED_Blink(LED_Port, BLUE_LED);
      FLAG_CLR(_LEDREG_, _LEDBUF_);
    }
  }
}
