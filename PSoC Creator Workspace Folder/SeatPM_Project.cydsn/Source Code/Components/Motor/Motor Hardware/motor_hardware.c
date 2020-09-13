/*==============================================================================
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design
Date: September 08 2020

File Name: motor_hardware.c
Author: Austin Pischer
File Description: This file contains the function definitions (implementations)
for the functions declared (prototyped) in motor_hardware.h. Please see
motor_hardware.h for a high level description of this set of functions.
==============================================================================*/

//==============================================================================
// Associated File Header 
//==============================================================================
#include "motor_hardware.h"

//==============================================================================
// Motor Setup 
//==============================================================================
void MotorHardware_Setup()
{
    Motor_Clock_Start();
    Motor_PWM_Start(); // Start motor pulse width modulation function generator
    MotorHardware_SetSpeed(0); // Stop motor
}

//==============================================================================
// Motor Hardware Set Speed 
//==============================================================================
void MotorHardware_SetSpeed(double Speed)
{
    // "Period" is recurring subsection of digital pwm signal
    // that is on until "compare" value is reached and is then off until
    // next period is reached.
    // Therefore compare cannot be larger than period.
    if(Speed <= Motor_PWM_ReadPeriod())
    {
         Motor_PWM_WriteCompare(Speed);
    }
}

//==============================================================================
// Motor Hardware Set Direction 
//==============================================================================
void MotorHardware_SetDirection(bool RetractFALSE_ReleaseTRUE)
{
    Motor_Direction_Write(RetractFALSE_ReleaseTRUE);
}

/* [] END OF FILE */