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
This is the "data model" class for the motor, which is separate from the
"hardware" functions outlined in the motor_hardware.h file.
=============================================================================*/

// Multiple Inclusion Protection
#ifndef MOTOR_H
#define MOTOR_H

//=============================================================================
// Inclusions
//=============================================================================
#include "project.h"
#include "parameter.h"
#include "motor_hardware.h"

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

/* Function Name: Motor_Constructor
Requirements: - Address of Motor instance
              - Timer/Counter/Pulse-Width-Modulation (TCPWM) component in
                the PSoC Creator Project's TopDesign.cysch
                configured in PWM mode with period of 100 and compare of 0,
                named "Motor_PWM"
              - Control register component in the PSoC Creator Project's
                TopDesign.cysch, configured with only 1 output,
                named "Motor_Direction"
Results: Motor instance data members and associated TopDesign components are
initialized and started-up, respectively.
*/
void Motor_Constructor(Motor *me);

/* Function Name: Motor_Stop
Requirements: Address of Motor instance
Results: Motor is stopped
*/
void Motor_Stop(Motor *me);

/* Function Name: Motor_GetDirection
Requirements: Address of Motor instance
Results: Returns direction of motor (enumerated to RETRACTING or RELEASING)
*/
Direction Motor_GetDirection(Motor *me);

/* Function Name: Motor_SetDirection
Requirements: - Address of Motor instance
              - New direction of motor (enumerated to RETRACTING or RELEASING)
Results: Motor direction is set in a direction that either retracts the user's
         ankle toward the motor or releases the user's ankle away from the motor.
*/
void Motor_SetDirection(Motor *me, Direction NewDirection);

/* Function Name: Motor_GetSpeed
Requirements: Address of Motor instance
Results: Returns the value of the Motor speed as stored in the Motor instance
*/
int Motor_GetSpeed(Motor *me);

/* Function Name: Motor_SetSpeed
Requirements: - Address of Motor instance
              - New speed value (currently valid range is 0-100 percent)
Results: Returns true if the speed was set to the passed New Speed, otherwise
         returns false.
         If true is returned, then to motor's speed has been sped up or slowed
         down to the new speed percent value.
*/
bool Motor_SetSpeed(Motor *me, int NewSpeed);

/* Function Name: Motor_GetPercentCableReleased
Requirements: Address of Motor instance
Results: Returns value of the "percent of cable released" as stored in the
         Motor instance.
*/
int Motor_GetPercentCableReleased(Motor *me);

/* Function Name: Motor_SetPercentCableReleased
Requirements: - Address of Motor instance
              - New percent value of cable to be released (can be more or less
                than current percent released, bounded by 0 or 100)
Results: Returns true if cable percent has been changed to the new value,
         otherwise returns false.
         If true is returned, then the motor will move in the retracting
         or releasing direction in order to make the cable percent released
         match that of the passed in new value.
*/
bool Motor_SetPercentCableReleased(Motor *me, int NewPercentCableReleased);

#endif
/* [] END OF FILE */
