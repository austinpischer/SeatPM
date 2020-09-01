/*==============================================================================
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design

File Name: parameter.h
Author: Austin Pischer

File Explanation:
A parameter is a bounded variable associated with the user's settings.
The parameters of the SeatPM are:
1. The minimum knee angle
2. The maximum knee angle
3. The speed of the device?
4. The amount of cable released from the device?
"Bounded" means that there is a minimum and maximum value
That the parameter cannot exceed in either direction.
The min/max value cannot be manipulated by the user
and are part of the behavior of the SeatPM device. 
Only the value can be manipulated by the user.
==============================================================================*/

// Start of multiple inclusion protection
#ifndef AUSTIN_PARAMTER_H
#define AUSTIN_PARAMTER_H

//=============================================================================
// Inclusions
//=============================================================================
#include "debug.h" // For bool 
#include <stdio.h> // For sprintf()
#include "project.h" // For PuTTY_UartPutString()

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
    double InvalidValue;
};

//=============================================================================
// Error Values
//=============================================================================
typedef enum Parameter_ValueValidationResult Parameter_ValueValidationResult;
enum Parameter_ValueValidationResult
{
    VALUE_VALID,
    VALUE_GREATER_THAN_MAXIMUM,
    VALUE_LESS_THAN_MINIMUM,
    VALUE_EQUAL_TO_INVALID,
    UNKNOWN_ERROR  
};

//=============================================================================
// Method Member Declarations - Parmater Class
//=============================================================================
bool Parameter_Constructor(Parameter *me,
                           double NewMinimumValue,
                           double NewMaximumValue,
                           double NewValue,
                           double NewInvalidValue);


bool Parameter_SetValue(Parameter *me, double NewValue);
double Parameter_GetValue(Parameter *me);
bool Parameter_SetMinimumValue(Parameter *me, double NewMinimumValue);
double Parameter_GetMinimumValue(Parameter *me);
bool Parameter_SetMaximumValue(Parameter *me, double NewMaximumValue);
double Parameter_GetMaximumValue(Parameter *me);
bool Parameter_IncrementValue(Parameter *me);
bool Parameter_DecrementValue(Parameter *me);
bool Parameter_IncrementMinimumValue(Parameter *me);
bool Parameter_DecrementMinimumValue(Parameter *me);
bool Parameter_IncrementMaximumValue(Parameter *me);
bool Parameter_DecrementMaximumValue(Parameter *me);
Parameter_ValueValidationResult Parameter_ValidateValue(Parameter *me);


#endif // End of multiple inclusion protection
/* [] END OF FILE */