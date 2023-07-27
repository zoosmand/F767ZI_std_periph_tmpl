/**
  ******************************************************************************
  * File Name          : srv_led.c
  * Description        : This file provides code for FreeRTOS LED service
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "freertos_srv.h"

/* Local variables -----------------------------------------------------------*/
static xTimerHandle xBlinkRedTimer = NULL;
static xTimerHandle xBlinkGreenTimer = NULL;


/* Function prototypes -------------------------------------------------------*/
static void prvBlinkRed(xTimerHandle);
static void prvBlinkGreen(xTimerHandle);





/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/**
  * @brief  Provides FreeRTOS LED service.
  * @return None
  */
void srvLed(void) {

  xBlinkRedTimer = xTimerCreate("BlinkRedTimer", (79/portTICK_RATE_MS), pdTRUE, (void*)0, prvBlinkRed);
  xBlinkGreenTimer = xTimerCreate("BlinkGreenTimer", (113/portTICK_RATE_MS), pdTRUE, (void*)0, prvBlinkGreen);

  xTimerStart(xBlinkRedTimer, 0);
  xTimerStart(xBlinkGreenTimer, 0);
}


/**
  * @brief  Blink rhe Red LED.
  * @return None
  */
static void prvBlinkRed(xTimerHandle xTimer) {
  LED_Blink(GPIOG, GPIO_BSRR_BS14_Pos);
}


/**
  * @brief  Blink rhe Green LED.
  * @return None
  */
static void prvBlinkGreen(xTimerHandle xTimer) {
  LED_Blink(GPIOG, GPIO_BSRR_BS13_Pos);
}

/*************************** © Zoo IPS, 2021 **********************************/
