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
                           double NewValue)
{
    char DebugString[64];
      
    // Assert that min <= max
    bool IsMin_LessThanOrEqualTo_Max = (NewMinimumValue <= NewMaximumValue);
    // Assert that min <= val
    bool IsMin_LessThanOrEqualTo_Value = (NewMinimumValue <= NewValue);
    // Assert that val <= max
    bool IsValue_lessThanOrEqualTo_Max = (NewValue <= NewMaximumValue);

    bool IsConstructorValid = 
        (IsMin_LessThanOrEqualTo_Max &&
        IsMin_LessThanOrEqualTo_Value &&
        IsValue_lessThanOrEqualTo_Max); 

    // Assign passed values to parameter
    if (IsConstructorValid == TRUE)
    {
        me->MinimumValue = NewMinimumValue;
        me->MaximumValue = NewMaximumValue;
        me->Value = NewValue;
        return TRUE; 
    }
    // Print Error Messages
    else
    {
        if(IsMin_LessThanOrEqualTo_Max == FALSE)
        {
            DEBUG_PRINT("ERROR: Minmum is greater than Maximum!\r\n");
            sprintf(DebugString, 
                    "%lf > %lf\r\n", 
                    NewMinimumValue, 
                    NewMaximumValue);
            DEBUG_PRINT(DebugString);
        }
        if(IsMin_LessThanOrEqualTo_Value == FALSE) 
        {
            DEBUG_PRINT("ERROR: Minimum is greater than value!\r\n");
            sprintf(DebugString, "%lf > %lf\r\n", NewMinimumValue, NewValue);
            DEBUG_PRINT(DebugString);
        }
        if(IsValue_lessThanOrEqualTo_Max == FALSE) 
        {
            DEBUG_PRINT("ERROR: Maximum is less than value!\r\n");
            sprintf(DebugString, "%lf < %lf\r\n", NewMaximumValue, NewValue);
            DEBUG_PRINT(DebugString);
        }
    } // End printing error messages
    return(IsConstructorValid);
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