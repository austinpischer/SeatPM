/*==============================================================================
 * Project: SeatPM
 * Team: Joint Effort
 * School: Seattle Pacific University
 * Class: CatalyzeU Senior Design
 * 
 * File Name: austin_parameter.c
 * Author: Austin Pischer
 * 
 * File Explanation:
 * Implements the functions declared in austin_parameter.h as part of
 * the Parameter class.
 *============================================================================*/

//=============================================================================
// Inclusions
//=============================================================================
#include "austin_parameter.h" // Associated header file

//*****************************************************************************
// Method Member Implementations - Parameter Class

//=============================================================================
// Constructor
//=============================================================================
bool Parameter_Constructor(Parameter *me,
                           double NewMinimumValue,
                           double NewMaximumValue,
                           double NewValue,
                           double NewInvalidValue)
{
     
    char DebugString[64];
    
    me->MinimumValue = NewMinimumValue;
    me->MaximumValue = NewMaximumValue;
    me->Value = NewValue;
    me->InvalidValue = NewInvalidValue;
    
    Parameter_ValueValidationResult Result = Parameter_ValidateValue(me);
    
    // Handle valid constructor (value==invlaid okay b/c this is constructor)
    if((me->MinimumValue <= me->MinimumValue) && 
       (Result == VALUE_VALID || Result == VALUE_EQUAL_TO_INVALID))
    {
        return(TRUE);
    }
    else // Print Error Messages
    {
        if((me->MinimumValue <= me->MinimumValue) == FALSE)
        {
            DEBUG_PRINT("ERROR: Minimum is greater than Maximum!\r\n");
            sprintf(DebugString, "%lf > %lf\r\n", me->MinimumValue, me->MaximumValue);
            DEBUG_PRINT(DebugString);
        }
        if(Result == VALUE_GREATER_THAN_MAXIMUM) 
        {
            DEBUG_PRINT("ERROR: Value is greater than maximum!\r\n");
            sprintf(DebugString, "%lf > %lf\r\n", me->Value, me->MaximumValue);
            DEBUG_PRINT(DebugString);
        }
        if(Result == VALUE_LESS_THAN_MINIMUM) 
        {
            DEBUG_PRINT("ERROR: Maximum is less than value!\r\n");
            sprintf(DebugString, "%lf > %lf\r\n", me->Value, me->MinimumValue);
            DEBUG_PRINT(DebugString);
        }
    } // End printing error message
    return(FALSE);
}

//=============================================================================
// Set Value
//=============================================================================                           
bool Parameter_SetValue(Parameter* me, double NewValue)
{
    if(NewValue <= me->MaximumValue && NewValue >= me->MinimumValue)
    {
        me->Value = NewValue;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
    
}

//=============================================================================
// Get Value 
//=============================================================================
double Parameter_GetValue(Parameter* me)
{
    return(me->Value);
}

//=============================================================================
// Set Minimum Value 
//=============================================================================
bool Parameter_SetMinimumValue(Parameter *me, double NewMinimumValue)
{
    // Minimum value should be less than or equal to current value
    // and less than or equal to than maximum value
    if(NewMinimumValue >= me->Value ||
       NewMinimumValue >= me->MaximumValue)
    {
        return FALSE;
    }
    else
    {
        me->MinimumValue = NewMinimumValue;
        return TRUE;
    }
}

//=============================================================================
// Get Minimum Value 
//=============================================================================
double Parameter_GetMinimumValue(Parameter *me)
{
    return(me->MinimumValue);
}

//=============================================================================
// Set Maximum Value 
//=============================================================================
bool Parameter_SetMaximumValue(Parameter *me, double NewMaximumValue)
{
    // Maximum value should be greater than or equal to current value
    // and greater than or equal to than minmum value
    if(NewMaximumValue <=  me->Value ||
       NewMaximumValue <= me->MinimumValue)
    {
        return FALSE;
    }
    else
    {
        me->MaximumValue = NewMaximumValue;
        return TRUE;
    }
}

//=============================================================================
// Get Maximum Value 
//=============================================================================
double Parameter_GetMaximumValue(Parameter *me)
{
    return(me->MaximumValue);
}

//=============================================================================
// Get Maximum Value 
//=============================================================================
bool Parameter_IncrementValue(Parameter *me)
{
    return(Parameter_SetValue(me, Parameter_GetValue(me)+1));
}

//=============================================================================
// Get Maximum Value 
//=============================================================================
bool Parameter_DecrementValue(Parameter *me)
{
    return(Parameter_SetValue(me, Parameter_GetValue(me)-1));
}

//=============================================================================
// Validate Value
//=============================================================================
Parameter_ValueValidationResult Parameter_ValidateValue(Parameter *me)
{
    if(me->Value > me->MaximumValue)
    {
        return(VALUE_GREATER_THAN_MAXIMUM);
    }
    else if(me->Value < me->MinimumValue)
    {
        return(VALUE_LESS_THAN_MINIMUM);
    }
    else if(me->Value == me->InvalidValue)
    {
        return(VALUE_EQUAL_TO_INVALID);
    }
    else
    {
        return(VALUE_VALID);
    }
    
}