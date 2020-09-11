/*==============================================================================
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design

File Name: austin_parameter.c
Author: Austin Pischer

File Explanation:
Implements the functions declared in parameter.h as part of
the Parameter class.
==============================================================================*/

//=============================================================================
// Inclusions
//=============================================================================
#include "parameter.h" // Associated header file

//*****************************************************************************
// Method Member Implementations - Parameter Class

//=============================================================================
// Constructor
//=============================================================================
bool Parameter_Constructor(Parameter *me,
                           double NewMinimum,
                           double NewMaximum,
                           double NewValue,
                           double NewInvalidValue)
{
     
    char DebugString[64];
    
    me->Minimum = NewMinimum;
    me->Maximum = NewMaximum;
    me->Value = NewValue;
    me->InvalidValue = NewInvalidValue;
    
    Parameter_ValueValidationResult Result = Parameter_ValidateValue(me);
    
    // Handle valid constructor (value==invlaid okay b/c this is constructor)
    if((me->Minimum <= me->Minimum) && 
       (Result == VALUE_VALID || Result == VALUE_EQUAL_TO_INVALID))
    {
        return(TRUE);
    }
    else // Print Error Messages
    {
        if((me->Minimum <= me->Minimum) == FALSE)
        {
            DEBUG_PRINT("ERROR: Minimum is greater than Maximum!\r\n");
            sprintf(DebugString, "%lf > %lf\r\n", me->Minimum, me->Maximum);
            DEBUG_PRINT(DebugString);
        }
        if(Result == VALUE_GREATER_THAN_MAXIMUM) 
        {
            DEBUG_PRINT("ERROR: Value is greater than maximum!\r\n");
            sprintf(DebugString, "%lf > %lf\r\n", me->Value, me->Maximum);
            DEBUG_PRINT(DebugString);
        }
        if(Result == VALUE_LESS_THAN_MINIMUM) 
        {
            DEBUG_PRINT("ERROR: Maximum is less than value!\r\n");
            sprintf(DebugString, "%lf > %lf\r\n", me->Value, me->Minimum);
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
double Parameter_GetMinimum(Parameter *me)
{
    return(me->Minimum);
}
double Parameter_GetMaximum(Parameter *me)
{
    return(me->Maximum);
}

//=============================================================================
// Set Functions
//=============================================================================                           
bool Parameter_SetValue(Parameter* me, double NewValue)
{
    if(NewValue <= me->Maximum && // Check upper bound
       NewValue >= me->Minimum)   // Check lower bound
    {
        me->Value = NewValue;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
    
}
bool Parameter_SetMinimum(Parameter *me, double NewMinimum)
{
    // min <= max
    if(NewMinimum <= me->Maximum)
    {
        me->Minimum = NewMinimum;
        return TRUE;
    }
    else
    {
        return(FALSE);
    }
}
bool Parameter_SetMaximum(Parameter *me, double NewMaximum)
{
    // max >= min,val
    if(NewMaximum >= me->Minimum)
    {
        me->Maximum = NewMaximum;
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
bool Parameter_IncrementMinimum(Parameter *me)
{
    return(Parameter_SetMinimum(me, Parameter_GetMinimum(me)+1));
}
bool Parameter_DecrementMinimum(Parameter *me)
{
    return(Parameter_SetMinimum(me, Parameter_GetMinimum(me)-1));
}

//=============================================================================
// Decrements
//=============================================================================
bool Parameter_DecrementValue(Parameter *me)
{
    return(Parameter_SetValue(me, Parameter_GetValue(me)-1));
}
bool Parameter_IncrementMaximum(Parameter *me)
{
    return(Parameter_SetMaximum(me, Parameter_GetMaximum(me)+1));
}
bool Parameter_DecrementMaximum(Parameter *me)
{
    return(Parameter_SetMaximum(me, Parameter_GetMaximum(me)-1));
}

//=============================================================================
// Validate Value
//=============================================================================
Parameter_ValueValidationResult Parameter_ValidateValue(Parameter *me)
{
    char debug[64];
    if(me->Value > me->Maximum) // Going over max
    {
        sprintf(debug, "\r\nERROR: [Value = %lf] > [Max = %lf]\r\n", me->Value, me->Maximum);
        DEBUG_PRINT(debug);
        return(VALUE_GREATER_THAN_MAXIMUM);
    }
    else if(me->Value < me->Minimum) // Going below min
    {
        sprintf(debug, "\r\nERROR:[Value = %lf] < [Min = %lf]\r\n", me->Value, me->Minimum);
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
        sprintf(debug, "\r\n[Value = %lf]\r\n[Max = %lf]\r\n[Min = %lf]\r\n", me->Value, me->Maximum, me->Minimum);
        DEBUG_PRINT(debug);
        return(VALUE_VALID);
    }
    
}