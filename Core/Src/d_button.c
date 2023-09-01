/**
  ******************************************************************************
  * @file          : d_button.c
  * @brief         : The file contains a set of functions and code snippets
  *                  specifically designed for handling buttons.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "d_button.h"

/* Private variables ---------------------------------------------------------*/
static uint32_t buttonCounterStart = 0;


/* Global variables ----------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  The function is designed to demonstrate the usage of a base timer
  * @param  p: a pointer to a struct that contains parameterss
  * @retval None
  */
void BtnPressDown(uint32_t *millis) {
  uint32_t lowThreshold = 50;
  uint32_t highThreshold = 150;
  if (buttonCounterStart == 0) {
    buttonCounterStart = *millis;
    // FLAG_SET(_EXTIREG_, _BTN0DPF_);
  } else {
    if ((*millis >= (buttonCounterStart + lowThreshold)) && (*millis < (buttonCounterStart + highThreshold))) {
      buttonCounterStart = 0;
      // Set Flag to toggle the Red LED
      if (PIN_LEVEL(BTN0_Port, BTN0_Pin)) {
        FLAG_SET(_LEDREG_, _LEDRUF_);
        // FLAG_CLR(_EXTIREG_, _BTN0DPF_);
      }
    } else {
      buttonCounterStart = 0;
    }
  }
}
