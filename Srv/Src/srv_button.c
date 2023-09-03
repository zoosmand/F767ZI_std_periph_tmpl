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
static TaskHandle_t xButtonHandler = NULL;
static uint32_t tickStartBtn = 0;

static void prvButtonHandler(void *pvParameters);

/* Global variables ----------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Provides FreeRTOS LED service.
  * @return None
  */
void srvButton(void) {
  xTaskCreate(prvButtonHandler, "Button Handler", configMINIMAL_STACK_SIZE, NULL, 1, &xButtonHandler);
}


/**
  * @brief  LED Indication
  * @return None
  */
static void prvButtonHandler(void *pvParameters) {

  while (1) {
    if (FLAG_CHECK(_EXTIREG_, _BTN0DF_)) {
      if (!(FLAG_CHECK(_EXTIREG_, _BTN0PDF_))) {
        tickStartBtn = xTaskGetTickCount(); 

        FLAG_SET(_EXTIREG_, _BTN0PDF_);
      }

      FLAG_CLR(_EXTIREG_, _BTN0DF_);
    }

    if (FLAG_CHECK(_EXTIREG_, _BTN0PDF_)) {
      if (xTaskGetTickCount() > tickStartBtn + 100) {
        if (PIN_LEVEL(BTN0_Port, BTN0_Pin)) {
          FLAG_SET(_EXTIREG_, _BTN0CLF_);
          tickStartBtn = xTaskGetTickCount();
        } else {
          tickStartBtn = 0;
        }
        FLAG_CLR(_EXTIREG_, _BTN0PDF_);
      }
    }

    if (FLAG_CHECK(_EXTIREG_, _BTN0CLF_)) {
      uint32_t tickNow = xTaskGetTickCount();
      if (!PIN_LEVEL(BTN0_Port, BTN0_Pin)) {
        if (tickNow <= tickStartBtn + 500) {
          FLAG_SET(_EXTIREG_, _BTN0ONCLF_);
        } else if ((tickNow > tickStartBtn + 2000) && (tickNow <= tickStartBtn + 3000)) {
          FLAG_SET(_EXTIREG_, _BTN0ONLCL2SF_);
        } else if ((tickNow > tickStartBtn + 4000) && (tickNow <= tickStartBtn + 6000)) {
          FLAG_SET(_EXTIREG_, _BTN0ONLCL4SF_);
        } else if ((tickNow > tickStartBtn + 8000) && (tickNow <= tickStartBtn + 12000)) {
          FLAG_SET(_EXTIREG_, _BTN0ONLCL8SF_);
        }

        tickStartBtn = 0;
        FLAG_CLR(_EXTIREG_, _BTN0CLF_);
      }
    }

    if (FLAG_CHECK(_EXTIREG_, _BTN0ONCLF_)) {
      BlinkRed();

      FLAG_CLR(_EXTIREG_, _BTN0ONCLF_);
    }

    if (FLAG_CHECK(_EXTIREG_, _BTN0ONLCL2SF_)) {
      printf("2s click\n");

      FLAG_CLR(_EXTIREG_, _BTN0ONLCL2SF_);
    }

    if (FLAG_CHECK(_EXTIREG_, _BTN0ONLCL4SF_)) {
      printf("4s click\n");

      FLAG_CLR(_EXTIREG_, _BTN0ONLCL4SF_);
    }

    if (FLAG_CHECK(_EXTIREG_, _BTN0ONLCL8SF_)) {
      printf("8s click\n");

      FLAG_CLR(_EXTIREG_, _BTN0ONLCL8SF_);
    }

  }
}
