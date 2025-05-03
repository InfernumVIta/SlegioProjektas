/**
 ********************************************************************************
 * @file    :LPS25HB.c
 * @author  :Vytautas Daunoras
 * @date    :2022-10-20
 ********************************************************************************
 */

#include "main.h"
#include "LPS25HB.h"

uint8_t chipID;
uint8_t datatowrite = 0;
uint8_t Pres_RAW[3];
uint32_t sl;


uint8_t LPS25HB_Initialise(I2C_HandleTypeDef * i2cHandle) {

  // Check the ID of the sensor.
  HAL_I2C_Mem_Read(i2cHandle, LPS25HB_ADDRESS, LPS25HB_WHO_AM_I, I2C_MEMADD_SIZE_8BIT, & chipID, 1, 100);

  if (chipID != LPS25HB_DEVICE_ID) {
    return 1; // If the ID does not match, initialization is aborted.
  } 

	// Power on the sensor.
  datatowrite = (0x01 << 7); //power on PD
  if (HAL_I2C_Mem_Write(i2cHandle, LPS25HB_ADDRESS, LPS25HB_CTRL_REG1, I2C_MEMADD_SIZE_8BIT, & datatowrite, 1, 100) != HAL_OK) {
    return 1;
  }
  return 0;
}


uint8_t LPS25HB_Measure_Presure_IT(I2C_HandleTypeDef * i2cHandle) {
	
	// Set one shot mode.
  datatowrite = (0x01 << 0); // One shot mode
	if (HAL_I2C_Mem_Write(i2cHandle, LPS25HB_ADDRESS, LPS25HB_CTRL_REG2, I2C_MEMADD_SIZE_8BIT, & datatowrite, 1, 100) != HAL_OK) {
		return 1;
	}

	// Start the measurement.
  HAL_I2C_Mem_Read_IT(i2cHandle, LPS25HB_ADDRESS, LPS25HB_PRESS_OUT_XL | 0x80, I2C_MEMADD_SIZE_8BIT, Pres_RAW, 3);

	return 0;
}


void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c) {
  if (hi2c->Instance == I2C2) {
  // The read operation for I2C2 is complete.
		
	sl = (Pres_RAW[2] << 16) |(Pres_RAW[1] << 8) | (Pres_RAW[0]);
  slegis=  sl / 4096.0f;

	Status=SAMPLE_READY;	
  }
}
