/**
  ******************************************************************************
  * File Name          : bmx280.h
  * Description        : This file provides headers for the code of the
  *                      configuration and measurment procedures for a BMx280
  *                      sensor.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BMX280_H
#define __BMX280_H


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Global variables ----------------------------------------------------------*/
extern uint32_t _BMX280REG_;
extern int32_t temperature;
extern uint32_t pressure;
extern uint32_t humidity;



/* Private defines -----------------------------------------------------------*/
typedef enum {
  BMP280  = 0x58,
  BME280  = 0x60
} BMx280_SensorTypeDef;

typedef enum {
  BMx280_SPI  = 0,
  BMx280_I2C
} BMx280_BusTypeDef;

typedef struct {  
  BMx280_SensorTypeDef sensorType;
  BMx280_BusTypeDef busType;
  I2C_TypeDef *bus;
} BMx280_ItemTypeDef;

#define BMX280_I2C_ADDR   (0x76 << 1)

#define BMX280_DEV_ID     0xd0
#define BMX280_CALIB1     0x88
#define BMX280_CALIB2     0xe1
#define BMX280_CTRL_HUM   0xf2
#define BMX280_CTRL_MEAS  0xf4
#define BMX280_STATUS     0xf3
#define BMX280_DATA       0xf7
#define BMX280_SETTINGS   0xf5
#define BMX280_RESET      0xe0
#define BMX280_RESET_VAL  0xb6

/* Types demanded by BMx280 datasheet */
typedef int32_t           BMx280_S32_t;
typedef uint32_t          BMx280_U32_t;

/* BMX280 Registry Flags */


extern ErrorStatus bmx280Status;

/* Exported functions prototypes ---------------------------------------------*/
ErrorStatus BMx280_Init(BMx280_ItemTypeDef*);
ErrorStatus BMx280_Measurment(BMx280_ItemTypeDef*, int32_t*);



#ifdef __cplusplus
}
#endif
#endif /*__BMX280_H */
