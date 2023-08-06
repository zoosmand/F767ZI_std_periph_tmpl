/**
  ******************************************************************************
  * @file          : freertos_srv.c
  * @brief         : This file containce code for different FreeRTOS services.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "freertos_srv.h"

/* Private variables ---------------------------------------------------------*/

/* Global variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static void SysTick_Run(void);

/* Private functions ---------------------------------------------------------*/
void FreeRTOS_Run(void) {
  
  /* services */  
  srvWatchdog();
  srvLed();
  srvLogger();
  srvUsart();

  /* core clock */
  SysTick_Run();
  
  /* run the scheduler */
  vTaskStartScheduler();
  // xPortStartScheduler();
}


/**
  * @brief  Sets up FreeRTOS core clock to 1kHz.
  * @return None
  */
static void SysTick_Run(void) {
  /* define SysTick peripherals */
  SET_BIT(SysTick->CTRL, (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk));
  SysTick->LOAD = RccClocks.HCLK_Freq / 1000U - 1U;
  SysTick->VAL = 0;
  SET_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk);
}


/**
  * @brief  Gets called when the runtime idles.
  * @return None
  */
void vApplicationIdleHook(void) {
volatile size_t xFreeStackSpace;
	xFreeStackSpace = xPortGetFreeHeapSize();

	if( xFreeStackSpace > 100 ) {
	}
}


/**
  * @brief  Gets called when stack overflows.
  * @return None
  */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char * pcTaskName) {
	(void) pcTaskName;
	(void) xTask;

	while (1);
}


/**
  * @brief  Gets called when memory allocation fails.
  * @return None
  */
void vApplicationMallocFailedHook(void) {
	while (1);
}





/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#if (configSUPPORT_STATIC_ALLOCATION == 1)

static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];                                              

/**
  * @brief  Gets called when configSUPPORT_STATIC_ALLOCATION equals to 1 and is required
  *         for static memory allocation support.
  * @return None
  */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize ) {
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}


/**
  * @brief  Gets called when configSUPPORT_STATIC_ALLOCATION equals to 1 and is required
  *         for static memory allocation support.
  * @return None
  */
void vApplicationGetTimerTaskMemory (StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize) {
  /* Timer task control block and stack */
  static StaticTask_t Timer_TCB;
  static StackType_t  Timer_Stack[configTIMER_TASK_STACK_DEPTH];

  *ppxTimerTaskTCBBuffer   = &Timer_TCB;
  *ppxTimerTaskStackBuffer = &Timer_Stack[0];
  *pulTimerTaskStackSize   = (uint32_t)configTIMER_TASK_STACK_DEPTH;
}

#endif

/*************************** © Zoo IPS, 2021 **********************************/
