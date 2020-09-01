/*==============================================================================
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design

File Name: accelerometer.h
Author: Austin Pischer

File Explanation:
This file defines the the "accelerometer" class (object-oriented c)

The accelerometer class should hold all data and perform all functions that
are independent of the specific hardware implementation of an accelerometer.

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
#include "debug.h"
#include "acceleration_vector.h"
#include "moving_average_filter.h"

//==============================================================================
// Type Definitions
//==============================================================================
/* Create a function pointer type for readability
that returns nothing and requires accelerometer pointer parameter */
typedef void (*Accelerometer_VirtualFunctionPointer)(Accelerometer *me);

//==============================================================================
// Data Members - Accelerometer Class
//==============================================================================
/* "typedef struct Accelerometer Accelerometer;" makes it so we can use the
type keyword "Accelerometer <instancename>" 
instead of "struct Accelerometer <instancename> */
typedef struct Accelerometer Accelerometer;
struct Accelerometer
{
    /* Normally base classes have a "virtual table" for the derived class
    to assign function implementations to.
    Since we only have one virtual function in this base class, we will skip
    making a vtable for the sake of simplicity.*/
    Accelerometer_VirtualFunctionPointer Accelerometer_UpdateCurrentAcceleration;
    AccelerationVector CurrentAcceleration;
    // Filter related data members:
    MovingAverageFilter Filter;
    AccelerationVector FilteredAcceleration;
};

//==============================================================================
// Method Declarations - Accelerometer Class
//==============================================================================

/* Function Name: Accelerometer_Constructor
Requirements: - Reference to Accelerometer instance
              - Function pointer to function implementation for the
                "Update Current Acceleration" virtual function
Returns: Passed Accelerometer Instance has data members initialized and virtual
functions pointed to derived class implementation.
*/
void Accelerometer_Constructor(Accelerometer *me,
                               Accelerometer_VirtualFunctionPointer Accelerometer_UpdateCurrentAcceleration_Pointer);

/* Function Name: Virtual_Accelerometer_UpdateCurrentAcceleration
Requirements: Reference to Accelerometer instance
Returns: Nothing
Note: This is the base class implementation of the virtual function
*/
void Virtual_Accelerometer_UpdateCurrentAcceleration(Accelerometer *me);

/* Function Name: Accelerometer_UpdateFilteredAcceleration
Requirements: Reference to Accelerometer instance
Returns: Updates the filtered acceleration member after sampling the current
acceleration and inserting the current acceleration into the filtering algorithm
*/
void Accelerometer_UpdateFilteredAcceleration(Accelerometer *me);

/* Function Name: GetCurrentAcceleration
Requirements: Reference to Accelerometer instance
Returns: Returns the instance of the current acceleration WITHOUT
updating it.
*/
AccelerationVector Accelerometer_GetCurrentAcceleration(Accelerometer *me);

/* Function Name: GetFilteredAcceleration
Requirements: Reference to Accelerometer instance
Returns: Returns the instance of the filtered acceleration WITHOUT
updating it.
*/
AccelerationVector Accelerometer_GetFilteredAcceleration(Accelerometer *me);
#endif // End of multiple inclusion protection.
       /* [] END OF FILE */