/*==============================================================================
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design
Date: September 08 2020

File Name: motor_hardware.h
Author: Austin Pischer
File Description: This file contains all the function declarations (prototypes)
related to the motor hardware/components of the SeatPM. It is meant to serve as
a layer of abstraction between direct calls to the PSoC Component APIs. It is
distinct from the fuctions in motor.h because those functions are related to
the motor struct data model. To decouple the data model and the component APIs,
this set of functions steps in.
==============================================================================*/

// Start of Multiple Inclusion Protection
#ifndef MOTOR_HARDWARE_H
#define MOTOR_HARDWARE_H

//==============================================================================
// Inclusions 
//==============================================================================
#include "project.h"
#include "debug.h" // for bool 

//==============================================================================
// Function Declarations 
//==============================================================================

/* Function Name: MotorHardware_Setup
Requirements: - Clock component in TopDesign.cysch named "Motor_Clock"
              - PWM componeent in TopDesign.cysch named "Motor_PWM"
Results: Starts the components and stops the motor.
*/
void MotorHardware_Setup();

/* Function Name: MotorHardware_SetSpeed
Requirements: - PWM component in TopDesign.cysch named "Motor_PWM"
              - Speed value between 0 to PWM period
Results: If speed is greater than PWM period then nothing happens, otherwise
         speed of motor changes to "compare" percent of max speed
*/
void MotorHardware_SetSpeed(double Speed);

/* Function Name: MotorHardware_SetDirection
Requirements: - Control Register component in TopDesign.cysch named 
                "Motor_Direction"
              - Boolean value where FALSE indicates retracting direction
                and TRUE indicates releasing direction
Results: Motor direction changes based on boolean value passed in
*/
void MotorHardware_SetDirection(bool RetractFALSE_ReleaseTRUE);

#endif // End of  Multiple Inclusion Protection
/* [] END OF FILE */
