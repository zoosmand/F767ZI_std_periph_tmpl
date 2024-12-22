/**
  ******************************************************************************
  * File Name          : i2c.h
  * Description        : This file provides code for the configuration
  *                      of the I2C instances.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __I2C_H
#define __I2C_H

#ifdef __cplusplus
  extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Global variables ----------------------------------------------------------*/
extern uint32_t _I2CREG_;

/* Private defines -----------------------------------------------------------*/
// PB9
#define I2C_2_SDA_Pin         GPIO_PIN_0
#define I2C_2_SDA_Pin_Pos     GPIO_PIN_0_Pos
#define I2C_2_SDA_Pin_Mask    GPIO_PIN_0_Mask
// PB8
#define I2C_2_SCL_Pin         GPIO_PIN_1
#define I2C_2_SCL_Pin_Pos     GPIO_PIN_1_Pos
#define I2C_2_SCL_Pin_Mask    GPIO_PIN_1_Mask
#define I2C_2_Port            GPIOF

/* Private typedef -----------------------------------------------------------*/
typedef enum {
  I2C_7bit    = 0,
  I2C_10bit   = 1
} I2C_AddressMode;

typedef enum {
  I2C_TX    = 0,
  I2C_RX    = 1
} I2C_Direction;

typedef enum {
  I2C_SOFTEND = 0,
  I2C_AUTOEND = 1
} I2C_RunMode;

/**
  * @brief  I2C operations timeout
  */
#define OP_TIMEOUT            500000U


/* Private macro -------------------------------------------------------------*/



/* Exported functions prototypes ---------------------------------------------*/
ErrorStatus I2C_Init(I2C_TypeDef *I2Cx);
ErrorStatus I2C_Write(I2C_TypeDef *I2Cx, uint8_t slaveAddr, uint8_t *buf, uint16_t len);
ErrorStatus I2C_Read(I2C_TypeDef *I2Cx, uint8_t slaveAddr, uint8_t reg, uint8_t *buf, uint16_t len);


#ifdef __cplusplus
}
#endif

#endif /* __I2C_H */
