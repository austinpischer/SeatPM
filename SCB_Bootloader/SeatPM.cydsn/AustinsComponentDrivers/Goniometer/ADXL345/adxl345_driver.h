/* ============================================================================
 *
 * Project: 
 *     SeatPM
 *     SPU CatalyzeU / SeniorDesign
 *     Joint Effort - Team 4
 * Author: 
 *      Austin Pischer
 * Date:
 *      2020-02-18
 *
 * File Name: 
 *      adxl345_driver.h
 * File Description:
 *      TODO
 *      
 * ============================================================================
*/

/* Multiple inclusion protection. See: austin_debug.h */
#ifndef ADXL_345_DRIVER_H
#define ADXL_345_DRIVER_H
    
#include "project.h"                // For type definitions, etc.
#include "adxl345_registers.h"      // Datasheet macros
#include "adxl345_i2c_addresses.h"  // Datasheet macros
#include "accelerometer_driver.h"   // ADXL345 *is an* accelerometer

#define ACCELEROMETER_READ_BUFFER_SIZE 10
#define ACCELEROMETER_WRITE_BUFFER_SIZE 10
    
#define SHANK_ACCELEROMETER_ADDRESS DEFAULT_ADDRESS
#define THIGH_ACCELEROMETER_ADDRESS ALTERNATE_ADDRESS
    
typedef struct ADXL345 ADXL345;
struct ADXL345
{
    Accelerometer Base;
    uint8 I2C_Address;
    uint8 ReadBuffer[ACCELEROMETER_READ_BUFFER_SIZE];
    uint8 WriteBuffer[ACCELEROMETER_WRITE_BUFFER_SIZE];
};

void ADXL345_InitializeConfigRegisters(ADXL345 *me);
void ADXL345_Constructor(ADXL345 *me);

/* Low Level */
void ADXL345_Read(ADXL345 *me, uint8 NumberOfBytesToRead);
void ADXL345_Write(ADXL345 *me, uint8 NumberOfBytesToWrite);

/* Mid Level */
void ADXL345_ReadDataRegisters(ADXL345 *me);
void ADXL345_WriteConfigRegister(ADXL345 *me, 
                                 const uint8 ConfigRegisterAddress,
                                 uint8 ByteToWrite);

/* High Level */
void ADXL345_CalculateCurrentAcceleration(ADXL345 *me);


/* Helper */
int16 ADXL345_CalculateComponentMagnitude(uint8 DataRegister0,
                                          uint8 DataRegister1);

#endif
/* [] END OF FILE */
