/*============================================================================= 
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design

File Name: motor.c
Author: Austin Pischer
File Description:
This file contains all the function implementations for the functions prototyped
in the associated file "motor.h" Please see that file for high level information
=============================================================================*/
#include "motor.h"

//=============================================================================
//  Motor Startup
//=============================================================================
void Motor_Constructor(Motor *me)
{
    // Initialize speed parameter
    double MinValue = 0;
    double MaxValue = 100;
    double Value = 0;
    bool IsValidConstructor =
        Parameter_Constructor(&(me->CurrentSpeed),
                              MinValue,
                              MaxValue,
                              Value,
                              INVALID_SPEED);

    if (IsValidConstructor == FALSE)
    {
        DEBUG_PRINT("Invalid CPM Speed Constructor");
    }

    // Cable released percent
    MinValue = 0;
    MaxValue = 100;
    Value = 0;
    IsValidConstructor =
        Parameter_Constructor(&(me->PercentCableReleased),
                              MinValue,
                              MaxValue,
                              Value,
                              INVALID_SPEED);

    Motor_Clock_Start();

    // Motor startup
    Motor_PWM_Start(); // This needs to be first but I'm not sure why

    // Set motor to be stopped at startup
    Motor_Stop(me);
}

//=============================================================================
//  Motor Get Direction
//=============================================================================
Direction Motor_GetDirection(Motor *me)
{
    return (me->CurrentDirection);
}

//=============================================================================
//  Motor Set Direction
//=============================================================================
void Motor_SetDirection(Motor *me, Direction NewDirection)
{
    // First thing is to return early if direction is not going to change.
    if (Motor_GetDirection(me) == NewDirection)
    {
        return;
    }

    // Set direction variable to new
    me->CurrentDirection = NewDirection;
    // Make hardware follow data
    Motor_Direction_Write(Motor_GetDirection(me));
    ;
}

//=============================================================================
//  Motor Get Speed
//=============================================================================
int Motor_GetSpeed(Motor *me)
{
    return (Parameter_GetValue(&(me->CurrentSpeed)));
}

//=============================================================================
//  Motor Set Speed
//=============================================================================
bool Motor_SetSpeed(Motor *me, int NewSpeed)
{
    // Don't do anything if speed isn't going to change
    // Set speed variable to new
    bool IsNewSpeedValid = Parameter_SetValue(&me->CurrentSpeed, NewSpeed);

    if (IsNewSpeedValid == TRUE)
    {
        // Make hardware follow data
        Motor_PWM_WriteCompare(Motor_GetSpeed(me));
    }
    else
    {
        DEBUG_PRINT("Invalid motor speed setting!");
    }
    return (IsNewSpeedValid);
}

//=============================================================================
//  Motor Stop
//=============================================================================
void Motor_Stop(Motor *me)
{
    Motor_SetSpeed(me, 0);
}

//=============================================================================
//  Motor Get Percent Cable Released
//=============================================================================
int Motor_GetPercentCableReleased(Motor *me)
{
    return (Parameter_GetValue(&(me->PercentCableReleased)));
}

//=============================================================================
//  Motor Set Percent Cable Released
//=============================================================================
bool Motor_SetPercentCableReleased(Motor *me, int NewPercentCableReleased)
{
    if (Motor_GetPercentCableReleased(me) == NewPercentCableReleased)
    {
        return (FALSE);
    }

    int CopyPercentCableReleased = Motor_GetPercentCableReleased(me);
    int PercentToChange;

    bool IsNewPercentCableReleasedValid =
        Parameter_SetValue(&(me->PercentCableReleased), NewPercentCableReleased);
    if (IsNewPercentCableReleasedValid == TRUE)
    {
        if (CopyPercentCableReleased > NewPercentCableReleased)
        {
            Motor_SetDirection(me, RELEASING);
            PercentToChange = NewPercentCableReleased - Motor_GetPercentCableReleased(me);
        }
        else
        {
            Motor_SetDirection(me, RETRACTING);
            PercentToChange = Motor_GetPercentCableReleased(me) - NewPercentCableReleased;
        }
        // Release to the new percentage
        Motor_SetSpeed(me, Parameter_GetMaximumValue(&(me->CurrentSpeed)));
        CyDelay(250 * PercentToChange);
        Motor_Stop(me);
    }
    else
    {
        DEBUG_PRINT("Invalid value to set percent of cable released!");
    }
    return (IsNewPercentCableReleasedValid);
}

/* [] END OF FILE */