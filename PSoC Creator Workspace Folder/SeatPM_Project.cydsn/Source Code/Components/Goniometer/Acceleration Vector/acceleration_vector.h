/*==============================================================================
 * Project: SeatPM
 * Team: Joint Effort
 * School: Seattle Pacific University
 * Class: CatalyzeU Senior Design
 * 
 * File Name: acceleration_vector.h
 * Author: Austin Pischer
 * 
 * File Explanation:
 * This file defines the class for "acceleration".
 * In physics, acceleration is defined as a quantity with
 * ~magnitude~ and ~direction~, also known as a ~vector~.
 * Since we live in a three dimensional world, we can express a single
 * acceleration vector as three different ~magnitudes~
 * in each of the three dimensional directions (x, y, and z directions).
 * In other words, a single vector can be expressed
 * in terms of its ~components~ along a frame of reference.
 * 
 * For example, we can assume force of gravity causes
 * a constant acceleration vector. 
 * However, two accelerometers at rest in different orientations
 * will report different component values.
 * Nevertheless, they are representing the same acceleration vector.
 *============================================================================*/

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
typedef int16 Component; 
    // Set as int16 because ADXL345 accelerometer gives
    // two 8 bit registers of data combined to 16 bit integer.    
    // Ideally this would be a templated structure, but C does not have
    // such a feature.
typedef struct AccelerationVector AccelerationVector;

//==============================================================================
// Data Members - AccelerationVector Class 
//==============================================================================
struct AccelerationVector 
{
    Component x,y,z;
};

//==============================================================================
// Method Declarations - AccelerationVector Class 
//==============================================================================
void AccelerationVector_Constructor(AccelerationVector *me);

#endif // End of multiple inclusion protection.
/* [] END OF FILE */
