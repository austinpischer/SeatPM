/*==============================================================================
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design

File Name: accelerometer_driver.h
Author: Austin Pischer

File Explanation:
This file defines the "Class" (Object-Oriented C) of an accelerometer.
See the following link  for more detail:
https://dmitryfrank.com/articles/oop_in_c

The accelerometer class should hold all data and perform all functions that
are independent of the specific hardware implementation of an accelerometer.

It is important to abstract from the hardware implementation because
it will be easier to update the project for a different accelerometer
in the future, if necessary.

Therefore, this class is considered the "base" class
and hardware implementations are the "derived" classes that must implement
the "virtual" UpdateCurrentAcceleration function on their own.
==============================================================================*/

// Start of multiple inclusion protection
#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

//==============================================================================
// Inclusions
//==============================================================================
#include "project.h"
#include "austin_debug.h"
#include "acceleration_vector.h"
#include "moving_average_filter.h"

//==============================================================================
// Type Definitions
//==============================================================================
// We define the Accelerometer type
// so that we can omit the "struct" keyword from following lines of code.
// This enforces the idea of a "class" over a separate data member struct
// with associated methods.
typedef struct Accelerometer Accelerometer;
typedef void (*Accelerometer_VirtualFunctionPointer)(Accelerometer *me);

//==============================================================================
// Data Members - Accelerometer Class 
//==============================================================================
struct Accelerometer
{
    Accelerometer_VirtualFunctionPointer Accelerometer_UpdateCurrentAcceleration;  
        /* NOTE: Normally, we would want only one virtual method table
                 for both the base class and for each derived class.
                 However, the simplicity of one function pointer for each
                 instance of the class outweighs the memory cost
                 since we only have 2 instances of the dervied class (ADXL345)
                 In the form of the 2 acceleormeters for the goniometer.
        */
    AccelerationVector CurrentAcceleration;
    AccelerationVector FilteredAcceleration;
    MovingAverageFilter Filter;
};

//==============================================================================
// Method Declarations - Accelerometer Class 
//==============================================================================
void Accelerometer_Constructor(Accelerometer *me, 
    Accelerometer_VirtualFunctionPointer Accelerometer_UpdateCurrentAcceleration_Pointer);
void Virtual_Accelerometer_UpdateCurrentAcceleration(Accelerometer *me);
void Accelerometer_UpdateFilteredAcceleration(Accelerometer *me);

#endif // End of multiple inclusion protection.
/* [] END OF FILE */