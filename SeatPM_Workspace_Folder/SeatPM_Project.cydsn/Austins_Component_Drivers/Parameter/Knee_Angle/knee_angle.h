/*============================================================================= 
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design

File Name: knee_angle.h
Author: Austin Pischer
File Description:
An "angle range" is three user set parameters: the minimum acceptable
angle, the maximum acceptable angle, and the current sampled angle.
=============================================================================*/

// Start of multiple inclusion protection
#ifndef KNEE_ANGLE_H
#define KNEE_ANGLE_H

//=============================================================================
// Include
//=============================================================================
#include "project.h"
#include "austin_parameter.h"
#include "emergency_stop.h"
#include "goniometer_driver.h" // for invalid angle value defitions

//=============================================================================
// Data Members
//=============================================================================
typedef struct KneeAngle KneeAngle;
struct KneeAngle
{
    Parameter Minimum, Current, Maximum;
};

//=============================================================================
// Method Members
//=============================================================================
void KneeAngle_Initialize(KneeAngle *me, 
                          double AbsoluteMinimum, 
                          double AbsoluteMaximum);
    
#endif // End of multiple inclusion protection
/* [] END OF FILE */
