/*==============================================================================
 * Project: SeatPM
 * Team: Joint Effort
 * School: Seattle Pacific University
 * Class: CatalyzeU Senior Design
 * 
 * File Name: adxl345.h
 * Author: Austin Pischer
 * 
 * File Explanation:
 * The ADXL345 is an accelerometer hardware implementation.
 * The ADXL345 class is a derived class from the Accelerometer base class.
 * The data and method members of the ADXL345 class should all be related to
 * the complexities involved with gathering data from an ADXL345.
 * This class also implements the virtual UpdateCurrentAcceleration function
 * from the Accelerometer class.
 *============================================================================*/

// Start of multiple inclusion protection
#ifndef ADXL345_DRIVER_H
#define ADXL345_DRIVER_H

//==============================================================================
// Inclusions
//==============================================================================
#include "project.h"
#include "acceleration_vector.h"
#include "moving_average_filter.h"
#include "accelerometer.h"
    
//==============================================================================
// Definitions
//==============================================================================
    
#define ADXL345_BUFFER_SIZE 10
    
//=============================================================================
// Data Members - ADXL345 Class
//=============================================================================
typedef struct ADXL345 ADXL345;
struct ADXL345
{
    Accelerometer Parent;
    uint8 I2C_Address;
    uint8 WriteBuffer[ADXL345_BUFFER_SIZE];
    uint8 ReadBuffer[ADXL345_BUFFER_SIZE];
};

//=============================================================================
// Method Members - ADXL345 Class
//=============================================================================
/* Object functions */
void ADXL345_Constructor(ADXL345 *me, uint8 My_I2C_Address);

/* Helper functions private to class */
int16 ADXL345_ConvertDataToComponent(uint8 ComponentDataRegister1, 
                                     uint8 ComponentDataRegister0);

/* Low Level */
void ADXL345_Write(ADXL345 *me, uint8 NumberOfBytesToWrite);
void ADXL345_Read(ADXL345 *me, uint8 NumberOfBytesToRead);

/* Mid Level (served by low level) */
void ADXL345_ReadDataRegisters(ADXL345 *me);
void ADXL345_WriteConfigRegister(ADXL345 *me,
                                 const uint8 ConfigRegisterAddress,
                                 uint8 ByteToWrite);

/* High Level (served by mid level) */
void ADXL345_InitializeConfigRegisters(ADXL345 *me);
void ADXL345_UpdateCurrentAcceleration(ADXL345 *me);

#endif // End of multiple inclusion protection.
/* [] END OF FILE */
