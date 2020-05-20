/*==============================================================================
 * Project: SeatPM
 * Team: Joint Effort
 * School: Seattle Pacific University
 * Class: CatalyzeU Senior Design
 * 
 * File Name: austin_parameter.h
 * Author: Austin Pischer
 * 
 * File Explanation:
 * A parameter is a bounded variable associated with the user's settings.
 * The parameters of the SeatPM are:
 * 1. The minimum knee angle
 * 2. The maximum knee angle
 * 3. The speed of the device?
 * 4. The amount of cable released from the device?
 * "Bounded" means that there is a minimum and maximum value
 * That the parameter cannot exceed in either direction.
 * The min/max value cannot be manipulated by the user
 * and are part of the behavior of the SeatPM device. 
 * Only the value can be manipulated by the user.
 *===========================================================================*/

// Start of multiple inclusion protection
#ifndef AUSTIN_PARAMTER_H
#define AUSTIN_PARAMTER_H

//=============================================================================
// Inclusions
//=============================================================================
#include "austin_debug.h" // For bool 

//=============================================================================
// Type definitions
//=============================================================================
typedef struct Parameter Parameter;

//=============================================================================
// Data Members - Parameter Class
//=============================================================================
struct Parameter
{
    double Value;
    double MinimumValue;
    double MaximumValue;
};

//=============================================================================
// Method Member Declarations - Parmater Class
//=============================================================================
bool Parameter_Constructor(Parameter *me,
                           double NewMinimumValue,
                           double NewMaximumValue,
                           double NewValue);
bool Parameter_SetValue(Parameter *me, double NewValue);
double Parameter_GetValue(Parameter *me);
bool Parameter_SetMinimumValue(Parameter *me, double NewMinimumValue);
double Parameter_GetMinimumValue(Parameter *me);
bool Parameter_SetMaximumValue(Parameter *me, double NewMaximumValue);
double Parameter_GetMaximumValue(Parameter *me);

#endif // End of multiple inclusion protection
/* [] END OF FILE */