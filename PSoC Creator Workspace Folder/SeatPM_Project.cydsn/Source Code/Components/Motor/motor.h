/*============================================================================= 
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design

File Name: motor.h
Author: Austin Pischer
File Description:
This file contains the data and method members for the Motor component.
The motor is what attaches to a spool of cable, which pulls the user's ankle
to create radial motion from the knee.
Any functions related to the motor should be implemented in this file and the
associated motor.c function implementation file.
=============================================================================*/

// Multiple Inclusion Protection
#ifndef MOTOR_H
#define MOTOR_H

//=============================================================================
// Inclusions
//=============================================================================
#include "project.h"
#include "parameter.h"
    
//=============================================================================
// Definitions
//=============================================================================  
#define INVALID_SPEED -1
    
//=============================================================================
// Define directions
//=============================================================================    
typedef enum Direction Direction;
enum Direction
{
    // TODO: Subject to change based on physical design on the motor.
    // These should always be boolean (0 or 1)
    RETRACTING = 0,
    RELEASING = 1
};

//=============================================================================
// Data Members
//=============================================================================
typedef struct Motor Motor;
struct Motor
{
    Parameter CurrentSpeed;
    Direction CurrentDirection;
    Parameter PercentCableReleased;
};

//=============================================================================
// Method Members
//=============================================================================

/* Function: Motor Startup
Description: Should be run before the infinite loop in main.
*/
void Motor_Startup(Motor *me);

/* Function: Motor Stop
Description: Sets the speed of the motor to zero.
*/
void Motor_Stop(Motor *me);


/* Function: Motor Get Direction
Description: Returns direction of motor passed in.
*/
Direction Motor_GetDirection(Motor *me);

/* Function: Motor Set Direction
Description: Sets direction of rotation of motor to release or retract cable.
*/
void Motor_SetDirection(Motor *me, Direction NewDirection);

/* Function: Motor Get Spedd
Description: Returns speed of motor within bounds of parameter set in startup.
*/
int Motor_GetSpeed(Motor *me);

/* Function: Motor Set Speed
Description: Returns true if passed speed is set, false if invalid or unchanged.
*/
bool Motor_SetSpeed(Motor *me, int NewSpeed);

/* Function: Motor Get Cable Released Percent
Description: Returns the amount of cable that has been released (0-100%)
// todo - more granularity with double values
*/
int Motor_GetPercentCableReleased(Motor *me);


/* Function: Motor Set Cable Released Percent
Description: Returns true if percent changes, otherwise unchanged or invalid.
// todo - more granularity with double values
*/
bool Motor_SetPercentCableReleased(Motor *me, int NewPercentCableReleased);

#endif
/* [] END OF FILE */
