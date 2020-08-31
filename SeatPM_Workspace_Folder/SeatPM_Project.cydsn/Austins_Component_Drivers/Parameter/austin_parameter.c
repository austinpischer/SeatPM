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
// Get Functions 
//=============================================================================
double Parameter_GetValue(Parameter* me)
{
    return(me->Value);
}
double Parameter_GetMinimumValue(Parameter *me)
{
    return(me->MinimumValue);
}
double Parameter_GetMaximumValue(Parameter *me)
{
    return(me->MaximumValue);
}

//=============================================================================
// Set Functions
//=============================================================================                           
bool Parameter_SetValue(Parameter* me, double NewValue)
{
    if(NewValue <= me->MaximumValue && // Check upper bound
       NewValue >= me->MinimumValue)   // Check lower bound
    {
        me->Value = NewValue;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
    
}
bool Parameter_SetMinimumValue(Parameter *me, double NewMinimumValue)
{
    // min <= max
    if(NewMinimumValue <= me->MaximumValue)
    {
        me->MinimumValue = NewMinimumValue;
        return TRUE;
    }
    else
    {
        return(FALSE);
    }
}
bool Parameter_SetMaximumValue(Parameter *me, double NewMaximumValue)
{
    // max >= min,val
    if(NewMaximumValue >= me->MinimumValue)
    {
        me->MaximumValue = NewMaximumValue;
        return TRUE;
    }
    else
    {
        return(FALSE);
    }
}
//=============================================================================
// Increments 
//=============================================================================
bool Parameter_IncrementValue(Parameter *me)
{
    return(Parameter_SetValue(me, Parameter_GetValue(me)+1));
}
bool Parameter_IncrementMinimumValue(Parameter *me)
{
    return(Parameter_SetMinimumValue(me, Parameter_GetMinimumValue(me)+1));
}
bool Parameter_DecrementMinimumValue(Parameter *me)
{
    return(Parameter_SetMinimumValue(me, Parameter_GetMinimumValue(me)-1));
}

//=============================================================================
// Decrements
//=============================================================================
bool Parameter_DecrementValue(Parameter *me)
{
    return(Parameter_SetValue(me, Parameter_GetValue(me)-1));
}
bool Parameter_IncrementMaximumValue(Parameter *me)
{
    return(Parameter_SetMaximumValue(me, Parameter_GetMaximumValue(me)+1));
}
bool Parameter_DecrementMaximumValue(Parameter *me)
{
    return(Parameter_SetMaximumValue(me, Parameter_GetMaximumValue(me)-1));
}

//=============================================================================
// Validate Value
//=============================================================================
Parameter_ValueValidationResult Parameter_ValidateValue(Parameter *me)
{
    char debug[64];
    if(me->Value > me->MaximumValue) // Going over max
    {
        sprintf(debug, "\r\nERROR: [Value = %lf] > [Max = %lf]\r\n", me->Value, me->MaximumValue);
        DEBUG_PRINT(debug);
        return(VALUE_GREATER_THAN_MAXIMUM);
    }
    else if(me->Value < me->MinimumValue) // Going below min
    {
        sprintf(debug, "\r\nERROR:[Value = %lf] < [Min = %lf]\r\n", me->Value, me->MinimumValue);
        DEBUG_PRINT(debug);
        return(VALUE_LESS_THAN_MINIMUM);
    }
    else if(me->Value == me->InvalidValue) // Invalid
    {
        sprintf(debug, "\r\nERROR:[Value = %lf] == [Invalid = %lf]\r\n", me->Value, me->InvalidValue);
        DEBUG_PRINT(debug);
        return(VALUE_EQUAL_TO_INVALID);
    }
    else
    {
        sprintf(debug, "\r\n[Value = %lf]\r\n[Max = %lf]\r\n[Min = %lf]\r\n", me->Value, me->MaximumValue, me->MinimumValue);
        DEBUG_PRINT(debug);
        return(VALUE_VALID);
    }
    
}