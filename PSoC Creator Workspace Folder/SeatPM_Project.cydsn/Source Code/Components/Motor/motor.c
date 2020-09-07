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
    me->CurrentDirection = RELEASING;

    // Initialize speed parameter
    double MinValue = 0;
    double MaxValue = 100;
    double Value = 0;
    bool IsValidConstructor = Parameter_Constructor(
        &(me->CurrentSpeed), MinValue, MaxValue, Value, INVALID_SPEED);

    if (IsValidConstructor == FALSE)
    {
        DEBUG_PRINT("Invalid CPM Speed Constructor");
    }

    // Initialize cable released percent parameter
    MinValue = 0;
    MaxValue = 100;
    Value = 0;
    IsValidConstructor = Parameter_Constructor(
        &(me->PercentCableReleased), MinValue, MaxValue, Value, INVALID_SPEED);
}

//=============================================================================
//  Motor Get Direction
//=============================================================================
Direction Motor_GetDirection(Motor *me) { return (me->CurrentDirection); }

//=============================================================================
//  Motor Get Speed
//=============================================================================
int Motor_GetSpeed(Motor *me)
{
    return (Parameter_GetValue(&(me->CurrentSpeed)));
}

//=============================================================================
//  Motor Get Percent Cable Released
//=============================================================================
int Motor_GetPercentCableReleased(Motor *me)
{
    return (Parameter_GetValue(&(me->PercentCableReleased)));
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
    MotorHardware_SetDirection(Motor_GetDirection(me));
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
        MotorHardware_SetSpeed(Motor_GetSpeed(me));
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
void Motor_Stop(Motor *me) { Motor_SetSpeed(me, 0); }

//=============================================================================
//  Motor Set Percent Cable Released
//=============================================================================
bool Motor_SetPercentCableReleased(Motor *me, int New_PercentCableReleased)
{
    // do nothing if percent wont change
    if (Motor_GetPercentCableReleased(me) == New_PercentCableReleased)
    {
        return (FALSE);
    }

    // Get current p.c.r. before changing it
    int Old_PercentCableReleased = Motor_GetPercentCableReleased(me);

    bool IsNewPercentCableReleasedValid = Parameter_SetValue(
        &(me->PercentCableReleased), New_PercentCableReleased);

    if (IsNewPercentCableReleasedValid == FALSE)
    {
        DEBUG_PRINT("Invalid value to set percent of cable released!");
        return (FALSE);
    }

    int PercentToRelease = 0;

    // If new greater than old, then we are releasing cable
    if (New_PercentCableReleased > Old_PercentCableReleased)
    {
        Motor_SetDirection(me, RELEASING);
        PercentToRelease = New_PercentCableReleased - Old_PercentCableReleased;
    }
    else  // retracting cable
    {
        Motor_SetDirection(me, RETRACTING);
        PercentToRelease = Old_PercentCableReleased - New_PercentCableReleased;
    }

    // Retract/release to the new percentage
    Motor_SetSpeed(me,50); // Start motor
    CyDelay(250 * PercentToRelease); // Keep motor going for amount of time
    Motor_Stop(me); // Stop motor
    
    return (TRUE);
}

/* [] END OF FILE */