/*==============================================================================
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design

File Name: acceleration_vector.h
Author: Austin Pischer

File Explanation:
This file declares the "acceleration vector" class.
A vector is defined as a magnitude and direction, which is represented
by three component magnitudes, one for each dimension of space (x,y,z).
==============================================================================*/

// Start of multiple inclusion protection
#ifndef ACCELERATION_VECTOR_H
#define ACCELERATION_VECTOR_H

//==============================================================================
// Inclusions
//==============================================================================
#include "project.h"

//==============================================================================
// Definitions
//==============================================================================
#define INVALID_COMPONENT_VALUE -32768

//==============================================================================
// Type Definitions
//==============================================================================
/* A component is an int16 because ADXL345 accelerometer gives two 8 bit
registers of data combined to 16 bit integer.*/
typedef int16 Component;

//==============================================================================
// Data Members
//==============================================================================
typedef struct AccelerationVector AccelerationVector;
struct AccelerationVector
{
    Component x, y, z;
};

//==============================================================================
// Method Members
//==============================================================================

/* Function Name: Accelleration Vector Constructor
Requirements: Reference to AccelerationVector instance
Returns: The passed in AccelerationVector instance has initialized data members
*/
void AccelerationVector_Constructor(AccelerationVector *me);

#endif // End of multiple inclusion protection.
/* [] END OF FILE */
