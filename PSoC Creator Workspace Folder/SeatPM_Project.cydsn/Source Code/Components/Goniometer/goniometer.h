/*============================================================================= 
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design

File Name: goniometer.h
Author: Austin Pischer
File Description:
A goniometer is an angle measurement device.
The SeatPM goniometer is made of two accelerometers.
This goniometer "class" also keeps track of its current angle its
moving-average angle (for example, the average of the last 5 current angles).
Please note that the current angle stored by the goniometer instance
is intended to be "raw data" that is then validated by the "knee angle" class.
=============================================================================*/

// Start of multiple inclusion protection
#ifndef GONIOMETER_DRIVER_H
#define GONIOMETER_DRIVER_H
    
//=============================================================================
// Inclusions
//=============================================================================
#include "project.h"
#include "adxl345.h"   
#include "acceleration_vector.h"
#include "adxl345_registers.h"
#include "debug.h"
#include <math.h>
#include <stdio.h>
    
//=============================================================================
// Definitions
//=============================================================================
#define INVALID_ANGLE -999
    
//=============================================================================
// Data Members
//=============================================================================
typedef struct Goniometer Goniometer;
struct Goniometer 
{
    ADXL345 Accelerometer_A, Accelerometer_B;
    double CurrentAngle;
    double FilteredAngle;
    
};

//==============================================================================
// Method Members
//==============================================================================

/* Function Name:  todo
Requirements: 
Results: 
*/
void Goniometer_Setup();

/* Function Name: Goniometer_Constructor
Requirements: Address of Goniometer instance
Results: Goniometer instance's data members are initialized
*/
void Goniometer_Constructor(Goniometer *me);

/* Function Name: Goniometer_Sample
Requirements: Address of Goniometer instance
Results: Current and Filtered Angle in Goniometer instance are updated after
the goniometer is sampled
*/
void Goniometer_Sample(Goniometer *me);

/* Function Name: Goniometer_GetCurrentAngle
Requirements: Address of Goniometer instance
Results: Returns value of the Current Angle as stored in goniometer instance.
To update the Current Angle and Filtered angle, use Goniometer_Sample()
*/
double Goniometer_GetCurrentAngle(Goniometer *me);

/* Function Name: Goniometer_GetFilteredAngle
Requirements: Address of Goniometer instance
Results: Returns value of the Filtered Angle as stored in goniometer instance.
To update the Current Angle and Filtered angle, use Goniometer_Sample()
*/
double Goniometer_GetFilteredAngle(Goniometer *me);

#endif
/* [] END OF FILE */
