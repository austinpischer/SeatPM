/*============================================================================= 
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design

File Name: knee_angle.c
Author: Austin Pischer
File Description: // TODO
=============================================================================*/

#include "knee_angle.h" // Associated file header

void KneeAngle_Initialize(KneeAngle *me, double AbsoluteMinimum, double AbsoluteMaximum)
{
    
    //=========================================================================
    // Intitialize Minimum Parameter
    //=========================================================================
    // The minimum angle value can be between the absolute minmum and the maximum angle
    // Since maximum angle value isn't set yet, just use maximum possible angle
    double MinValue = AbsoluteMinimum;
    double MaxValue = AbsoluteMaximum;
    double Value = AbsoluteMinimum;
    bool IsValidConstructor = 
        Parameter_Constructor(&me->Minimum,
                              MinValue,
                              MaxValue,
                              Value,
                              INVALID_ANGLE);

    if(IsValidConstructor == FALSE)
    {
        DEBUG_PRINT("Invalid Minimum Angle Constructor");
        // Knee angle settings are critical to user safety.
        // Shut off the device to prevent injuring the user.
        EmergencyStop();
    }
    // Otherwise, constructor called with valid min, max and value
    
    //=========================================================================
    // Intitialize Maximum Parameter
    //=========================================================================
    // The maximum angle can be between the absolute maximum and the minimum
    MinValue = Parameter_GetValue(&me->Minimum);
    MaxValue = AbsoluteMaximum;
    Value = AbsoluteMaximum;

    IsValidConstructor =
     Parameter_Constructor(&me->Maximum,
                            MinValue,
                            MaxValue,
                            Value,
                            INVALID_ANGLE);

    if(IsValidConstructor == FALSE)
    {
        DEBUG_PRINT("Invalid Maximum Angle Constructor");
        // Knee angle settings are critical to user safety.
        // Shut off the device to prevent injuring the user.
        EmergencyStop();
    }
    // Otherwise, constructor called with valid min, max and value

    //=========================================================================
    // Intitialize Current Parameter
    //=========================================================================
    MinValue = Parameter_GetValue(&me->Minimum);
    MaxValue = Parameter_GetValue(&me->Maximum);
    Value = MinValue; // dummy value
    IsValidConstructor =
        Parameter_Constructor(&me->Current,
                              MinValue,
                              MaxValue,
                              Value,
                              INVALID_ANGLE);
        
    if(IsValidConstructor == FALSE)
    {
        DEBUG_PRINT("Invalid Current Angle Constructor");
    }
}
/* [] END OF FILE */
