/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef ADXL345_DRIVER_H
#define ADXL345_DRIVER_H

#include "project.h"
#include "acceleration_vector.h"
#include "moving_average_filter.h"
#include "accelerometer_driver.h"
    
#define ADXL345_BUFFER_SIZE 10
    
typedef struct ADXL345 ADXL345;
struct ADXL345
{
    Accelerometer Parent;
    uint8 I2C_Address;
    uint8 WriteBuffer[ADXL345_BUFFER_SIZE];
    uint8 ReadBuffer[ADXL345_BUFFER_SIZE];
};
void ADXL345_Constructor(ADXL345 *me, uint8 My_I2C_Address);
void ADXL345_Write(ADXL345 *me, uint8 NumberOfBytesToWrite);
void ADXL345_Read(ADXL345 *me, uint8 NumberOfBytesToRead);
void ADXL345_ReadDataRegisters(ADXL345 *me);
void ADXL345_WriteConfigRegister(ADXL345 *me, const uint8 ConfigRegisterAddress, uint8 ByteToWrite);
void ADXL345_InitializeConfigRegisters(ADXL345 *me);
int16 ADXL345_ConvertDataToComponent(uint8 ComponentDataRegister1, uint8 ComponentDataRegister0);
void ADXL345_UpdateCurrentAcceleration(ADXL345 *me);
#endif 
/* [] END OF FILE */
