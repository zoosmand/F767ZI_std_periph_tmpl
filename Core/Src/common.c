/**
  ******************************************************************************
  * @file           : common.c
  * @brief          : The C code file provides a collection of commonly used 
  *                   routines along with the printf() function for outputting
  *                   data.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
 
 
/* Includes ------------------------------------------------------------------*/
#include "common.h"

/* Global variables ----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
__STATIC_INLINE uint32_t ITM_SendCharChannel(uint32_t ch, uint32_t channel);
__STATIC_INLINE void _putc(uint8_t ch);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void) {
  while (1) {
    //
  }
}



/********************************************************************************/
/*                         printf() output supply block                         */
/********************************************************************************/
/**
  * @brief send a symbol into the ITM (Instrumentation Trace Macrocell) channel
  *        on an STM32F767 microcontroller. This symbol can be captured using
  *        the SWO (Serial Wire Output) pin on the microcontroller, allowing for
  *        debugging and monitoring of the system. 
  * @param ch: a symbol to be output
  * @param channel: number of an ITM channel
  * @retval the same symbol 
  */
__STATIC_INLINE uint32_t ITM_SendCharChannel(uint32_t ch, uint32_t channel) {
   /* ITM enabled and ITM Port enabled */
  if (((ITM->TCR & ITM_TCR_ITMENA_Msk) != 0UL) && ((ITM->TER & (1 << channel)) != 0UL)) {
    while (ITM->PORT[channel].u32 == 0UL) {
      __NOP();
    }
    ITM->PORT[channel].u8 = (uint8_t)ch;
  }
  return (ch);
}



/**
  * @brief  Sends a character into a debug device. 
  * @param ch: the character to output
  * @retval none: 
  */
__STATIC_INLINE void _putc(uint8_t ch) {
  if (ch == '\n') _putc('\r');

  #ifdef SWO_ITM
    ITM_SendCharChannel(ch, 0);
  #endif

  #ifdef SWO_USART
    USART3->TDR = ch;
    while (!(PREG_CHECK(USART3->ISR, USART_ISR_TXE_Pos)));
  #endif
}



/**
  * @brief An interpretation of the __weak system _write()
  * @param file: IO file
  * @param ptr: pointer to a char(symbol) array
  * @param len: length of the char array to ouitput
  * @retval length of the array 
  */
int _write(int32_t file, char *ptr, int32_t len) {
  for(int32_t i = 0 ; i < len ; i++) {
    _putc(*ptr++);  
  }
	return len;
}
/********************************************************************************/
/*                                 end of block                                 */
/********************************************************************************/



#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, int line) { 
  printf("Wrong parameters value: file %s on line %d\n", file, line);
}
#endif /* USE_FULL_ASSERT */
