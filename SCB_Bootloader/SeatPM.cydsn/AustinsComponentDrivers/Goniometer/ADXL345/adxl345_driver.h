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
 *      This is the "header file" containing the object-oriented C "class"
 *      named "ADXL345".
 *      An ADXL345 is a hardware implementation of an accelerometer.
 *      (An ADXL345 *is an* accelerometer, inheritance relationship)
 *
 *      In the SeatPM project, two ADXL345's communicate with the
 *      microcontroller over the I2C communication protocol, 
 *      where the microcontroller is the primary (master) device
 *      and the ADXL345's are the secondary (slave) devices 
 *
 *
 *      
 * ============================================================================
*/

/* Multiple inclusion protection. See: austin_debug.h */
#ifndef ADXL_345_DRIVER_H
#define ADXL_345_DRIVER_H

#include "project.h"               // For type definitions, etc.
#include "adxl345_registers.h"     // Datasheet macros
#include "accelerometer_driver.h"  // ADXL345 *is an* accelerometer
#include <stdio.h>                 // For sprintf

#define ACCELEROMETER_READ_BUFFER_SIZE 10
#define ACCELEROMETER_WRITE_BUFFER_SIZE 10

#define SHANK_ACCELEROMETER_ADDRESS DEFAULT_ADDRESS
#define THIGH_ACCELEROMETER_ADDRESS ALTERNATE_ADDRESS

// Define the type "struct <tag>" as type "<tag>"
typedef struct ADXL345 ADXL345;

//========================= ADXL345 Data Members =================================
struct ADXL345
{
    Accelerometer Base;
    uint8 I2C_Address;
    uint8 ReadBuffer[ACCELEROMETER_READ_BUFFER_SIZE];
    uint8 WriteBuffer[ACCELEROMETER_WRITE_BUFFER_SIZE];
};

//========================= ADXL345 Method Prototypes =================================
void ADXL345_Constructor(ADXL345 *me);
/* Low Level Communication Functions */
void ADXL345_Read(ADXL345 *me, uint8 NumberOfBytesToRead);
void ADXL345_Write(ADXL345 *me, uint8 NumberOfBytesToRead);
/* Mid Level Communication Functions */
void ADXL345_ReadDataRegisters(ADXL345 *me);
void ADXL345_WriteConfigRegister(ADXL345 *me, const uint8 ConfigRegisterAddress, uint8 ByteToWrite);
/* High Level Communication Functions */
void ADXL345_InitializeConfigurationRegisters(ADXL345 *me);
/* Data Processing Functions */
int16 ADXL345_CalculateComponentMagnitude(uint8 DataRegister0, uint8 DataRegister1);
void ADXL345_CalculateCurrentAcceleration(ADXL345 *me);

#endif
/* [] END OF FILE */
