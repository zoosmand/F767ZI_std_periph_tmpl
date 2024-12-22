/**
  ******************************************************************************
  * File Name          : i2c.c
  * Description        : This file provides code for the configuration
  *                      of the I2C instances.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "i2c.h"

/* Global variables ---------------------------------------------------------*/
uint32_t _I2CREG_;


/* -------------------------------------------------------------------------- */
/* Private function prototypes -----------------------------------------------*/
/* -------------------------------------------------------------------------- */
static ErrorStatus I2C_PrepareTransmit(I2C_TypeDef *I2Cx, uint16_t slaveAddr, I2C_AddressMode addrMode, I2C_Direction dir, I2C_RunMode runMode, uint32_t bufLength);
static ErrorStatus I2C_Master_Send(I2C_TypeDef *I2Cx, uint16_t slaveAddr, uint8_t *buf, uint32_t len);
static ErrorStatus I2C_Master_Receive(I2C_TypeDef *I2Cx, uint16_t slaveAddr, uint8_t *buf, uint16_t len);









////////////////////////////////////////////////////////////////////////////////
/**
  * @brief  Initializes I2C3 peripheral
  * @param  None
  * @return None
  */
ErrorStatus I2C_Init(I2C_TypeDef *I2Cx) {

  if (I2Cx == I2C2) {
    /** I2C4 GPIO Configuration    
        PF0      ------> I2C2_SDA
        PF1      ------> I2C2_SCL 
    */
    /* ----------------------------------------------------------------------------- */
    /* Mode */
    #define I2C_2_MASK  (I2C_2_SDA_Pin_Mask | I2C_2_SCL_Pin_Mask)
    MODIFY_REG(I2C_2_Port->MODER, I2C_2_MASK, (
        (_MODE_AF << (I2C_2_SDA_Pin_Pos * 2))
      | (_MODE_AF << (I2C_2_SCL_Pin_Pos * 2))
    ));
    /* Speed */
    MODIFY_REG(I2C_2_Port->OSPEEDR, I2C_2_MASK, (
        (_SPEED_H << (I2C_2_SDA_Pin_Pos * 2))
      | (_SPEED_H << (I2C_2_SCL_Pin_Pos * 2))
    ));
    /* Output type */
    MODIFY_REG(I2C_2_Port->OTYPER, (I2C_2_SDA_Pin | I2C_2_SCL_Pin), (
        (_OTYPE_OD << I2C_2_SDA_Pin_Pos)
      | (_OTYPE_OD << I2C_2_SCL_Pin_Pos)
    ));
    /* Push mode */
    MODIFY_REG(I2C_2_Port->PUPDR, I2C_2_MASK, (
        (_PUPD_PU << (I2C_2_SDA_Pin_Pos * 2))
      | (_PUPD_PU << (I2C_2_SCL_Pin_Pos * 2))
    ));
    /* Alternate function */
    MODIFY_REG(I2C_2_Port->AFR[1], 0x000000ff, (
        (GPIO_AF_4 << (I2C_2_SDA_Pin_Pos * 4))
      | (GPIO_AF_4 << (I2C_2_SCL_Pin_Pos * 4))
      //   (GPIO_AF_4 << ((I2C_2_SDA_Pin_Pos - 8) * 4))
      // | (GPIO_AF_4 << ((I2C_2_SCL_Pin_Pos - 8) * 4))
    ));

    /* Due to a undocumented bug, the source clock should be start after the GPIO initialization */
    Delay(1);
    PREG_SET(RCC->APB1ENR, RCC_APB1ENR_I2C2EN_Pos);


    // I2C
    /* ----------------------------------------------------------------------------- */
    CLEAR_BIT(I2Cx->CR1, I2C_CR1_PE);
    I2Cx->TIMINGR = (0x40912732 & 0xf0ffffff);
    // I2Cx->TIMINGR = (0x20404768 & 0xf0ffffff);
    SET_BIT(I2Cx->OAR1, I2C_OAR1_OA1EN);
    // SET_BIT(I2Cx->CR2, (I2C_CR2_AUTOEND | I2C_CR2_NACK));
    I2Cx->OAR2 = 0;
    MODIFY_REG(I2Cx->CR1, (I2C_CR1_GCEN_Msk | I2C_CR1_NOSTRETCH_Msk), 0);
    SET_BIT(I2Cx->CR1, I2C_CR1_PE);

    return (SUCCESS);
  }

  return (ERROR);
}






/**
  * @brief  Writes 8 bit data via I2C
  * @param  I2Cx: pointer to an I2C instance
  * @param  data: a byte to send
  * @return None
  */
ErrorStatus I2C_Write(I2C_TypeDef *I2Cx, uint8_t slaveAddr, uint8_t *buf, uint16_t len) {
  if (I2C_Master_Send(I2Cx, slaveAddr, buf, len)) {
    return (ERROR);
  }
  return (SUCCESS);
}






/**
  * @brief  Reads 8 bit data via I2C
  * @param  I2Cx: pointer to an I2C instance
  * @return  a received byte
  */
ErrorStatus I2C_Read(I2C_TypeDef *I2Cx, uint8_t slaveAddr, uint8_t reg, uint8_t *buf, uint16_t len) {
  if (I2C_Master_Send(I2Cx, slaveAddr, &reg, 1)) {
    return (ERROR);
  } else {
    if (I2C_Master_Receive(I2Cx, slaveAddr, buf, len)) {
      return (ERROR);
    }
  }
  return (SUCCESS);
}






/**
  * @brief  Transmits in master mode an amount of data.
  * @param  I2Cx Pointer to a I2C_TypeDef I2Cx.
  * @param  slaveAddress Target I2Cx address: The I2Cx 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface
  * @param  buf Pointer to data buffer
  * @param  len Amount of data to be sent
  * @return transmit status
  */
ErrorStatus I2C_Master_Send(I2C_TypeDef *I2Cx, uint16_t slaveAddr, uint8_t *buf, uint32_t len) {
  uint32_t timeout = OP_TIMEOUT;

  I2C_AddressMode mode;
  mode = ((slaveAddr & 0xfe) == slaveAddr) ? I2C_7bit : I2C_10bit;

  if (I2C_PrepareTransmit(I2Cx, slaveAddr, mode, I2C_TX, I2C_SOFTEND, len)) {
    return (ERROR);
  }

  while (len--) {
    I2Cx->TXDR = (__O uint8_t)*buf++;
    while (!(PREG_CHECK(I2Cx->ISR, I2C_ISR_TXE_Pos))) {
      timeout--;
      if (!timeout) {
        return (ERROR);
      }
    }
  }

  return (SUCCESS);
}






/**
  * @brief  Receives in master mode an amount of data.
  * @param  I2Cx Pointer to a I2C_TypeDef I2Cx.
  * @param  slaveAddress Target I2Cx address: The I2Cx 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface
  * @param  buf Pointer to data buffer
  * @param  len Amount of data to be sent
  * @return receive status
  */
ErrorStatus I2C_Master_Receive(I2C_TypeDef *I2Cx, uint16_t slaveAddr, uint8_t *buf, uint16_t len) {
  uint32_t timeout = OP_TIMEOUT;

  I2C_AddressMode mode;
  mode = ((slaveAddr & 0xfe) == slaveAddr) ? I2C_7bit : I2C_10bit;

  if (I2C_PrepareTransmit(I2Cx, slaveAddr, mode, I2C_RX, I2C_AUTOEND, len)) {
    return (ERROR);
  }
  
  while (len--) {
    while (!(PREG_CHECK(I2Cx->ISR, I2C_ISR_RXNE_Pos))) {
      timeout--;
      if (!timeout) {
        return (ERROR);
      }
    }
    *buf++ = (__I uint8_t)I2Cx->RXDR;
  }

  return (SUCCESS);
}






static ErrorStatus I2C_PrepareTransmit(I2C_TypeDef *I2Cx, uint16_t slaveAddr, I2C_AddressMode addrMode, I2C_Direction dir, I2C_RunMode runMode, uint32_t len) {
  uint32_t timeout = OP_TIMEOUT;
  uint32_t cnt = 0;
  cnt = (len > 255) ? 255 : len;

  if (runMode == I2C_SOFTEND) {
    while (PREG_CHECK(I2Cx->ISR, I2C_ISR_BUSY_Pos)) {
      timeout--;
      if (!timeout) {
        return (ERROR);
      }
    }
  } 
  
  switch (addrMode) {
    case I2C_7bit:
      MODIFY_REG(I2Cx->CR2, (I2C_CR2_SADD_Msk | I2C_CR2_NBYTES_Msk | I2C_CR2_RD_WRN_Msk | I2C_CR2_START_Msk | I2C_CR2_STOP_Msk), (
          (slaveAddr << I2C_CR2_SADD_Pos)
        | (dir << I2C_CR2_RD_WRN_Pos)
        | (cnt << I2C_CR2_NBYTES_Pos)
        | (runMode << I2C_CR2_AUTOEND_Pos)
        | I2C_CR2_START
      ));
      break;
    
    case I2C_10bit:
      /* ToDo. 10-bit address handler */
      break;
    
    default:
      break;
  }

  /* Return error id the I2C address was not accepted */
  if ((PREG_CHECK(I2Cx->ISR, I2C_ISR_NACKF_Pos)) && (PREG_CHECK(I2Cx->ISR, I2C_ISR_STOPF_Pos))) {
    return (ERROR);
  }

  return(SUCCESS);
}

