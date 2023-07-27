/**
  ******************************************************************************
  * @file          : srv_watchdog.c
  * @brief         : This file contains code for FreeRTOS Watchdog service
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "freertos_srv.h"

/* Private variables ---------------------------------------------------------*/
static TimerHandle_t xWatchdogRechargeTimer = NULL;

/* Global variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static void prvWatchdogRecharge(TimerHandle_t);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Provides FreeRTOS Watchdog service.
  * @return None
  */
void srvWatchdog(void) {
  
  xWatchdogRechargeTimer = xTimerCreate("WatchdogRechargeTimer", (1000/portTICK_PERIOD_MS), pdTRUE, (void*)0, prvWatchdogRecharge);

  xTimerStart(xWatchdogRechargeTimer, 0);
}


/**
  * @brief  Recharges Watchdog counter.
  * @return None
  */
static void prvWatchdogRecharge(TimerHandle_t xTimer) {
  WRITE_REG(IWDG->KR, IWDG_KEY_RELOAD);
}
