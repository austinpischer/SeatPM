/*==============================================================================
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design

File Name: adxl345.h
Author: Austin Pischer

File Explanation:
The ADXL345 is an accelerometer hardware implementation.
The ADXL345 class is a derived class from the Accelerometer base class.
The data and method members of the ADXL345 class should all be related to
the complexities involved with gathering data from an ADXL345.
This class also implements the virtual UpdateCurrentAcceleration function
from the Accelerometer class.
==============================================================================*/

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

/* Function Name: ADXL345_Constructor
Requirements: - Reference to ADXL345 Instance,
              - 8 bit I2C Address as defined in adxl345_registers.h
              - SCB component in the PSoC Creator Project's TopDesign.cysch
                configured as I2C in "Master" mode named "I2C"
Results: ADXL345 instance has data members initialized and TopDesign components
         are started up.
*/
void ADXL345_Constructor(ADXL345 *me, uint8 My_I2C_Address);

/* Function Name: ADXL345_UpdateCurrentAcceleration
Requirements: Reference to ADXL345 Instance
Results: CurrentAcceleration vector (in the instance's parent) is updated after
sampling the ADXL345 hardware (according to the ADXL345 instance's I2C_Address).
*/
void ADXL345_UpdateCurrentAcceleration(ADXL345 *me);

#endif // End of multiple inclusion protection.
/* [] END OF FILE */
