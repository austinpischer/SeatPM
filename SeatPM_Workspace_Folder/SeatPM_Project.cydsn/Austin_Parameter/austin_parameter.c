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
    // Minimum Value cannot be greater than Maximum Value or Value.
    // Value cannot be greater than Maximum Value
    if(NewMinimumValue > NewMaximumValue || // Equivalent to Maximum >= Minimum
       NewMinimumValue > NewValue ||        // Equivalnet to Value >= Minimum
       NewValue < NewMaximumValue)          // Equivalent to Maximum >= Value
    {
        return FALSE;
    }
    else
    {
        me->MinimumValue = NewMinimumValue;
        me->MaximumValue = NewMaximumValue;
        me->Value = NewValue;
        return TRUE;
    }
    
}

//=============================================================================
// Set Value
//=============================================================================                           
bool Parameter_SetValue(Parameter* me, double NewValue)
{
    if(NewValue <= me->MaximumValue && NewValue >= me->MinimumValue)
    {
        me->Value = NewValue;
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