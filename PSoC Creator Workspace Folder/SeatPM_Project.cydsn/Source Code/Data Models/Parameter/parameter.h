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
    double Minimum;
    double Maximum;
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

/* Function Name: Parameter_Constructor
Requirements: - Address of Parameter instance
              - The minimum value that the Value member can be
              - The maximum value that the Value member can be
              - The initial value of the Value member
              - The value at which the Value member will always be invalid
Results: Returns bool if min<=val<=max and val != inval
*/
bool Parameter_Constructor(Parameter *me,
                           double NewMinimum,
                           double NewMaximum,
                           double NewValue,
                           double NewInvalidValue);

/* Function Name: Parameter_ValidateValue
Requirements: Address of Parameter instance.
Results: Enumerated integer within Parameter_ValueValidationResult
         that represents the validity of the Value member of the Parameter
         instance.
*/
Parameter_ValueValidationResult Parameter_ValidateValue(Parameter *me);


//==============================================================================
// Simple get functions 
//==============================================================================

/* Function Name: Parameter_GetValue
Requirements: Address of Parameter instance
Results: Returns value of Value member of instance 
*/
double Parameter_GetValue(Parameter *me);

/* Function Name: Parameter_GetMinimum
Requirements: Address of Parameter instance
Results: Returns value of Minimum member of instance 
*/
double Parameter_GetMinimum(Parameter *me);

/* Function Name: Parameter_GetMaximum
Requirements: Address of Parameter instance
Results: Returns value of Maximum member of instance 
*/
double Parameter_GetMaximum(Parameter *me);


//==============================================================================
//  Set functions
//==============================================================================

/* Function Name: Parameter_SetValue
Requirements: - Address of Parameter instance
              - New value of Value member of instance
Results: - Returns true if min<=value<=max and val!=inval
           and Value member of instance is set to value of NewValue
         - Otherwise returns false
*/
bool Parameter_SetValue(Parameter *me, double NewValue);

/* Function Name: Parameter_SetMinimum
Requirements: - Address of Parameter instance
              - New value of Minimum member of instance
Results: - Returns true if min<=value<=max and val!=inval
           and Minimum member of instance is set to value of NewMinimum
         - Otherwise returns false
*/
bool Parameter_SetMinimum(Parameter *me, double NewMinimum);

/* Function Name: Parameter_SetMaximum
Requirements: - Address of Parameter instance
              - New value of Maximum member of instance
Results: - Returns true if min<=value<=max and val!=inval
           and Maximum member of instance is set to value of NewMaximum
         - Otherwise returns false
*/
bool Parameter_SetMaximum(Parameter *me, double NewMaximum);


//==============================================================================
// Simple increment/decrement functions 
//==============================================================================

/* Function Name: Parameter_IncrementValue
Requirements: - Address of Parameter instance
Results: - Returns true if min<=value<=max and val!=inval
           and Value member of instance is incremeneted by 1
         - Otherwise returns false
*/
bool Parameter_IncrementValue(Parameter *me);

/* Function Name: Parameter_DecrementValue
Requirements: - Address of Parameter instance
Results: - Returns true if min<=value<=max and val!=inval
           and Value member of instance is decremeneted by 1
         - Otherwise returns false
*/
bool Parameter_DecrementValue(Parameter *me);

/* Function Name: Parameter_IncrementMinimum
Requirements: - Address of Parameter instance
Results: - Returns true if min<=value<=max and val!=inval
           and Minimum member of instance is incremeneted by 1
         - Otherwise returns false
*/
bool Parameter_IncrementMinimum(Parameter *me);

/* Function Name: Parameter_DecrementMinimum
Requirements: - Address of Parameter instance
Results: - Returns true if min<=value<=max and val!=inval
           and Minimum member of instance is decremeneted by 1
         - Otherwise returns false
*/
bool Parameter_DecrementMinimum(Parameter *me);

/* Function Name: Parameter_IncrementMaximum
Requirements: - Address of Parameter instance
Results: - Returns true if min<=value<=max and val!=inval
           and Maximum member of instance is incremeneted by 1
         - Otherwise returns false
*/
bool Parameter_IncrementMaximum(Parameter *me);

/* Function Name: Parameter_DecrementMaximum
Requirements: - Address of Parameter instance
Results: - Returns true if min<=value<=max and val!=inval
           and Maximum member of instance is decremeneted by 1
         - Otherwise returns false
*/
bool Parameter_DecrementMaximum(Parameter *me);

#endif // End of multiple inclusion protection
/* [] END OF FILE */