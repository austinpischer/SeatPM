/*==============================================================================
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design
Date: September 08 2020

File Name: user_interface_states.h
Author: Austin Pischer
File Description: 
==============================================================================*/

// Start of Multiple Inclusion Protection
#ifndef USER_INTERFACE_STATES_H
#define USER_INTERFACE_STATES_H

//==============================================================================
// Inclusions 
//==============================================================================
#include "user_interface.h"

//==============================================================================
// Configuration States 
//==============================================================================

/* Function Name: UserInterface_Initial_State
Requirements: - Should be called via FSM_Constructor() in
                UserInterface_Constructor() 
              - Address of UserInterface instance
              - Address of Event instance (containing UI signal and other data) 
Results: - Prints "Welcome To SeatPM" to screen
         - Transitions to Set Minimum Knee Angle State automatically 
*/
void UserInterface_Initial_State(UserInterface *me, Event const *event);

/* Function Name: UserInterface_SetMinimumKneeAngle_State
Requirements: - Address of UserInterface instance
              - Address of Event instance (containing UI signal and other data)
Results: - Prompts user to set minimum knee angle
         - Transitions to set maximum angle state after confirm button pressed
*/
void UserInterface_SetMinimumKneeAngle_State(UserInterface *me,
                                             Event const *event);

/* Function Name: UserInterface_SetMaximumKneeAngle_State
Requirements: - Address of UserInterface instance
              - Address of Event instance (containing signal and other data)
Results: - Prompts user to set minimum knee angle
         - Transitions to Goniometer Reading Check State after 
           confirm button pressed
*/
void UserInterface_SetMaximumKneeAngle_State(UserInterface *me,
                                             Event const *event);

/* Function Name: UserInterface_GoniometerReadingCheck_State
Requirements: - Address of UserInterface instance
              - Address of Event instance (containing signal and other data)
Results: - Prompts user to attach goniometer
         - Prints error if angle is invalid/out of bounds
         - Transitions to Ankle Strap Retract/Release state after confirm
           button is pressed and reading is valid
*/
void UserInterface_GoniometerReadingCheck_State(UserInterface *me,
                                                Event const *event);

/* Function Name: UserInterface_AnkleStrapRetractRelease_State
Requirements: - Address of UserInterface instance
              - Address of Event instance (containing signal and other data)
Results: - Prompts user to attach ankle strap
         - Prompts user to retract or release the cable to make it easier
           for the user to attach the ankle strap
         - Transitions to Confirm CPM Startup State after confirm button
           is pressed
*/
void UserInterface_AnkleStrapRetractRelease_State(UserInterface *me,
                                                  Event const *event);

//==============================================================================
// Continuous Passive Motion States 
//==============================================================================

/* Function Name: UserInterface_ConfirmCPMStartup_State
Requirements: - Address of UserInterface instance
              - Address of Event instance (containing signal and other data)
Results: - Prompts user to start continuous passive motion at low speed
         - Transitions to CPM State after confirm button is pressed 
         - Starts the motor at low speed
*/
void UserInterface_ConfirmCPMStartup_State(UserInterface *me,
                                           Event const *event);

/* Function Name: UserInterface_ContinuousPassiveMotion_State
Requirements: - Address of UserInterface instance
              - Address of Event instance (containing signal and other data)
Results: - Displays runtime and current angle
         - Motor runs
         - Transitions to Confirm Speed Change State if increment or decrement
           button pressed
         - Transitions to Confirm CPM Startup State and stops motor if
           confirm or back button is pressed
*/
void UserInterface_ContinuousPassiveMotion_State(UserInterface *me,
                                                 Event const *event);

/* Function Name: UserInterface_ConfirmSpeedChange_State
Requirements: - Address of UserInterface instance
              - Address of Event instance (containing signal and other data)
Results: - Displays new and current motor speed
         - Transitions to CPM state and changes speed to new after confirm 
           button is pressed (speed does not change if back is pressed
*/
void UserInterface_ConfirmSpeedChange_State(UserInterface *me,
                                            Event const *event);

#endif // End of Multiple Inclusion Protection
/* [] END OF FILE */