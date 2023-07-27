/**
  ******************************************************************************
  * @file          : freertos_srv.h
  * @brief         : This file provides code for the configuration
  *                      of FreeRTOS and its services.
  ******************************************************************************
  * @attention
  * 
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FREERTOS_SRV_H
#define __FREERTOS_SRV_H
#ifdef __cplusplus
  extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "list.h"
#include "timers.h"

/* Exported functions prototypes ---------------------------------------------*/
void FreeRTOS_Run(void);

/* Services */
void srvWatchdog(void);
// void srvLed(void);
void srvLogger(void);


#ifdef __cplusplus
}
#endif
#endif /*__FREERTOS_SRV_H */
